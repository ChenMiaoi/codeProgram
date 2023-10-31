#include "global.h"

#include <cstdio>
#include <cstdlib>
#include <string>

global_t global_config {};
elf_t elf_config {};

void global_init() {
    INFO("entry global init function!");
    elf_config.elf_code_start = elf_config.elf_header_len + ELF_START;
    
    // global_config.source        = new char[MAX_SOURCE];
    global_config.types         = new type_t[MAX_TYPES + sizeof(type_t)];
    global_config.funcs         = new func_t[MAX_FUNCS + sizeof(func_t)];
    global_config.blocks        = new block_t[MAX_BLOCKS + sizeof(block_t)];
    global_config.aliases       = new alias_t[MAX_ALIASES + sizeof(alias_t)];
    global_config.macros        = new macro_t[MAX_ALIASES + sizeof(macro_t)];
    global_config.func_tries    = new trie_t[MAX_FUNC_TRIES + sizeof(trie_t)];
    global_config.ph1_ir        = new ph1_ir_t[MAX_IR_INSTR + sizeof(ph1_ir_t)];
    global_config.ph2_ir        = new ph2_ir_t[MAX_IR_INSTR + sizeof(ph2_ir_t)];
    global_config.global_ir     = new ph1_ir_t[MAX_GLOBAL_IR + sizeof(ph1_ir_t)];
    global_config.label_lut     = new label_lut_t[MAX_LABEL + sizeof(label_lut_t)];
    global_config.constants     = new constant_t[MAX_CONSTANTS + sizeof(constant_t)];

    elf_config.elf_code         = new char[MAX_CODE];
    elf_config.elf_data         = new char[MAX_DATA];
    elf_config.elf_header       = new char[MAX_HEADER];
    elf_config.elf_symtab       = new char[MAX_SYMTAB];
    elf_config.elf_strtab       = new char[MAX_STRTAB];
    elf_config.elf_section      = new char[MAX_SECTION];

    global_config.funcs[0].stack_size = 4;
}

type_t* global_t::add_type() {
    return &types[types_idx++];
}

type_t* global_t::add_type_name(const std::string &name) {
    type_t* type = add_type();
    type->type_name = name;
    return type;
}

type_t* global_t::add_type_name(const std::string& name, const base_type_t base) {
    type_t* type = add_type();
    type->type_name = name;

    switch (base) {
    case TYPE_VOID: 
        type->base_type = TYPE_VOID; 
        type->size = 0;
        break;
    case TYPE_CHAR: 
        type->base_type = TYPE_CHAR;
        type->size = 1;
        break;
    case TYPE_INT:  
        type->base_type = TYPE_INT;
        type->size = 4;
        break;
    case TYPE_STRUCT: 
        type->base_type = TYPE_STRUCT;
        // TODO
        break;
    default:
        FATAL("error type!");
        exit(1);
    }
    return type;
}

block_t* global_t::add_block(block_t *parent, func_t *func, macro_t *macro) {
    block_t* blk = &blocks[blocks_idx];
    blk->index = blocks_idx++;
    blk->parent = parent;
    blk->func = func;
    blk->macro = macro;
    blk->next_local = 0;

    return blk;
}

void elf_t::elf_add_symbol(std::string symbol, int len, int pc) {
    elf_write_symbol_int(elf_strtab_index);
    elf_write_symbol_int(pc);
    elf_write_symbol_int(0);
    elf_write_symbol_int(pc == 0 ? 0 : 1 << 16);

    elf_strtab += symbol;
    elf_strtab_index += len;
    elf_strtab[elf_strtab_index++] = 0;
    elf_symbol_index++;
}

void elf_t::elf_write_symbol_int(int val) {

}