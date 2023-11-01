#include "defs.h"
#include <functional>
#include <string>

func* func::add_func(const std::string& name, int& funcs_index, trie_t* func_tries, int& func_tries_index) {
    func_t * fn = nullptr;
    int index = func_tries->insert_trie(name, funcs_index, func_tries_index);
    if (index == funcs_index) {
        fn = &this[funcs_index++];
        fn->return_def.var_name = name;
    }
    fn = &this[index];
    fn->stack_size = 4;
    return fn;
}

int trie::insert_trie(const std::string& name, int func_index, int& func_tries_index) {
    std::function<int(trie_t*, const std::string&, int, int&)> __insert_trie = 
    [&](trie_t* trie, const std::string& name, int func_index, int& func_tries_index) {
        char first_char = name[0];
        int fc = static_cast<int>(first_char);
        // INFO("fc = " + std::to_string(fc));
        info << "fc = " << std::to_string(fc);

        if (!fc) {
            if (!trie->index)
                trie->index = func_index;
            return trie->index;
        }
        // INFO("trie->index = " + std::to_string(trie->index));
        info << "trie->index = " << trie->index;

        if (!trie->next[fc]) {
            trie->next[fc] = func_tries_index++;
            for (int i = 0; i < 128; i++)
                trie[trie->next[fc]].next[i] = 0;
            trie[trie->next[fc]].index = 0;
        }
        return __insert_trie(&trie[trie->next[fc]], name.substr(1), func_index, func_tries_index);
    };

    return __insert_trie(this, name.substr(1), func_index, func_tries_index);
}

type_t* type::add_type(int &type_idx) {
    return &this[type_idx++];
}

void type::add_type_name(const std::string& name) {
    type_name = name;
}

void type::add_type_name(const std::string& name, const base_type_t base) {
    type_name = name;
    switch (base) {
    case TYPE_VOID: 
        base_type = TYPE_VOID; 
        size = 0;
        break;
    case TYPE_CHAR: 
        base_type = TYPE_CHAR;
        size = 1;
        break;
    case TYPE_INT:  
        base_type = TYPE_INT;
        size = 4;
        break;
    case TYPE_STRUCT: 
        base_type = TYPE_STRUCT;
        // TODO
        break;
    default:
        // FATAL("error type!");
        fatal << "error type!";
        exit(1);
    }
}

block_t* block_t::add_block(int index, block_t *parent, func_t *func, macro_t *macro) {
    block_t* blk = &this[index];
    blk->index      = index;
    blk->parent     = parent;
    blk->func       = func;
    blk->macro      = macro;
    blk->next_local = 0;

    return blk;
}

void alias::add_alias(int& aliases_idx, const std::string &alias, const std::string &value) {
    alias_t* al = &this[aliases_idx++];
    al->alias     = alias;
    al->value     = value;
    al->disabled  = false;
}