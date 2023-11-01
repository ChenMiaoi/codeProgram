#ifndef __DEFS_H__
#define __DEFS_H__

#include "../../config"
#include "../util/util.h"

#include <string>
#include <vector>
#include <functional>

constexpr const int MAX_CODE        = 262144;
constexpr const int MAX_DATA        = 262144;
constexpr const int MAX_HEADER      = 1024;
constexpr const int MAX_SYMTAB      = 65536;
constexpr const int MAX_STRTAB      = 65536;
constexpr const int MAX_SECTION     = 1024;

constexpr const int MAX_TYPES       = 64;
constexpr const int MAX_FUNCS       = 256;
constexpr const int MAX_LABEL       = 4096;
constexpr const int MAX_SOURCE      = 262144;
constexpr const int MAX_BLOCKS      = 750;
constexpr const int MAX_ALIASES     = 1024;
constexpr const int MAX_IR_INSTR    = 32768;
constexpr const int MAX_GLOBAL_IR   = 256;
constexpr const int MAX_CONSTANTS   = 1024;
constexpr const int MAX_FUNC_TRIES  = 1356;

constexpr const int ELF_START       = 0x10000;
constexpr const int REG_COUNT       = 8;

struct opcode;
struct var;
struct macro;
struct func;
struct block_t;
struct ph1_ir;
struct label_lut;
struct regfile;
struct ph2_ir;
struct type;
struct alias;
struct constant;
struct trie;

/*
* 
**/
typedef struct opt {

} opcode_t;

/*
* `var`变量定义
**/
typedef struct var {
    constexpr static int MAX_TYPE_LEN = 32;
    constexpr static int MAX_VAR_LEN  = 32;

    std::string type_name;          // 类型名
    std::string var_name;           // 变量名
    bool        is_ptr;             // 判断指针
    bool        is_func;            // 判断函数
    bool        is_global;          // 判断全局
    int         array_size;         // 类型大小
    int         offset;             // 偏移量
    int         init_var;           // 初始化数据
    int         liveness;           // 生命周期
    int         in_loop;            // 循环？
} var_t;

typedef struct macro {
    constexpr static int MAX_VAR_LEN = 32;
    constexpr static int MAX_PARAMS  = 8;

    std::string        name;
    bool               is_variadic;         // 可变参
    int                start_source_idx;    // 宏在源代码中的起始位置
    std::vector<var_t> param_defs;          // 宏的参数定义
    int                num_param_defs;      // 宏参数定义的数量
    std::vector<int>   params;              // 实际传递给宏的参数
    int                num_params;          // 传递参数的数量
    bool               disabled;            // 宏是否被禁用
} macro_t;

typedef struct func {
    constexpr static int MAX_PARAMS = 8;

    var_t               return_def;         // 返回值定义
    std::vector<var_t>  params_def;         // 形参列表定义
    int                 num_params;         // 形参列表个数
    bool                is_va_args;         // 是否是可变参
    int                 stack_size;         // 函数堆栈大小，总是开始在第四字节

    func* add_func(const std::string& name, int& funcs_index, trie* func_tries, int& func_tries_index);
} func_t;

typedef struct block_t {
    constexpr static int MAX_LOCALS = 900;

    std::vector<var_t>  locals;             // 块内的局部变量
    int                 next_local;         // 下一个可用局部变量的索引
    block_t*            parent;             // 指向当前块的父块
    func_t*             func;               // 表示当前块所属的函数
    macro_t*            macro;              // 当前块所属的宏
    int                 locals_size;        // 局部变量数量
    int                 index;              // 当前块索引

    block_t* add_block(int index, block_t *parent, func_t *func, macro_t *macro);
} block_t;

typedef struct ph1_ir {
    constexpr static int MAX_VAR_LEN = 32;

    opcode_t    op;                         // 操作符
    std::string func_name;                  // 函数名
    int         param_num;                  // 参数数量
    int         size;                       // 大小
    var_t*      dest;
    var_t*      src1;
    var_t*      src2;
} ph1_ir_t;

typedef struct label_lut {
    constexpr static int MAX_VAR_LEN = 32;

    std::string name;                       // 标签名
    int         offset;                     // 偏移距离
} label_lut_t;

typedef struct regfile {
    var_t*  var;
    bool    polluted;                       // 判断寄存器变量是否被污染
} regfile_t;

typedef struct ph2_ir {
    constexpr static int MAX_VAR_LEN = 32;

    opcode_t            op;
    int                 src0;
    int                 src1;
    int                 dest;
    std::string         func_name;
    std::vector<char>   true_label;
    std::vector<char>   false_label;    
} ph2_ir_t;

typedef enum base_type {
    TYPE_VOID,
    TYPE_INT,
    TYPE_CHAR,
    TYPE_STRUCT,
} base_type_t;

typedef struct type {
    constexpr static int MAX_TYPE_LEN = 32;
    constexpr static int MAX_FILEDS   = 32;

    std::string         type_name;          // 类型名
    base_type_t         base_type;          // 基本类型
    int                 size;               // 类型大小
    std::vector<var_t>  fields;             // 字段
    int                 num_fields;         // 字段数量

    type* add_type(int& type_idx);
    void add_type_name(const std::string& name);
    void add_type_name(const std::string& name, const base_type_t base);
} type_t;

typedef struct lvalue {
    int         size;                       // 左值大小
    bool        is_ptr;                     // 判断指针
    bool        is_func;                    // 判断函数
    bool        is_reference;               // 判断引用
    type_t*     type;                       // 左值类型
} lvalue_t;

typedef struct alias {
    constexpr static int MAX_VAR_LEN = 32;

    std::string alias;                      // 假名名称
    std::string value;                      // 变量名
    bool        disabled;                   // 是否可用

    void add_alias(int& aliases_idx, const std::string &alias, const std::string &value);
} alias_t;

/*
* 枚举中的常量类型
**/
typedef struct constant {
    constexpr static int MAX_VAR_LEN = 32;

    std::string alias;                      // 名称
    int         value;                      // 枚举值
} constant_t;

/*
* 字典树trie
**/
typedef struct trie {
    int index;                              // 索引值
    int next[128];                          // 当前节点的子节点

    int insert_trie(const std::string& name, int func_index, int& func_tries_index);
} trie_t;

#endif //! __DEFS_H__