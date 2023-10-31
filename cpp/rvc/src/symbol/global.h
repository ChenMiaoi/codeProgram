#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "../defs.h"
#include "../util/util.h"

#include <string>
#include <vector>

typedef struct global {
    int blocks_idx      = 0;
    int macros_idx      = 0;
    int funcs_idx       = 1;
    int func_tries_idx  = 1;
    int types_idx       = 0;
    int global_ir_idx   = 0;
    int ph1_ir_idx      = 0;
    int ph2_ir_idx      = 0;
    int label_lut_idx   = 0;
    int aliases_idx     = 0;
    int constants_idx   = 0;
    int source_idx      = 0;

    block_t*                blocks;
    macro_t*                macros;
    func_t*                 funcs;
    trie_t*                 func_tries;
    type_t*                 types;
    ph1_ir_t*               global_ir;
    ph1_ir_t*               ph1_ir;
    ph2_ir_t*               ph2_ir;
    label_lut_t*            label_lut;
    std::vector<regfile_t>  reg;
    alias_t*                aliases;
    constant_t*             constants;
    
    std::string             source;

    type_t* add_type();
    type_t* add_type_name(const std::string& name);
    type_t* add_type_name(const std::string& name, const base_type_t base);

    block_t* add_block(block_t* parent, func_t* func, macro_t* macro);
} global_t;

typedef struct elf {
    int elf_code_idx        = 0;
    int elf_data_idx        = 0;
    int elf_code_start;
    int elf_header_idx      = 0;
    int elf_header_len      = 0x54; // ELF fixed: 0x34 + 1 * 0x20

    int elf_symbol_index;
    int elf_symtab_index;
    int elf_strtab_index;
    int elf_section_index;

    std::string elf_code;
    std::string elf_data;
    std::string elf_header;
    std::string elf_symtab;
    std::string elf_strtab;
    std::string elf_section;

    void elf_add_symbol(std::string symbol, int len, int pc);
    void elf_write_symbol_int(int val);
} elf_t;

extern void global_init();

#endif //! __GLOBAL_H__S