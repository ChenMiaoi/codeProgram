#include "global.h"

#include <cstdio>
#include <cstdlib>
#include <string>

global_t global_config {};
elf_t elf_config {};

void global_init() {
    // INFO("entry global init function!");
    info << "entry global init function!";
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

type_t* global_t::add_type_name(const std::string &name) {
    type_t* type = types->add_type(types_idx);
    type->add_type_name(name);
    return type;
}

type_t* global_t::add_type_name(const std::string& name, const base_type_t base) {
    type_t* type = types->add_type(types_idx);
    type->add_type_name(name, base);
    // INFO(type->type_name + " " + std::to_string(type->base_type));
    info << type->type_name << " " << std::to_string(type->base_type);
    return type;
}

block_t* global_t::add_block(block_t *parent, func_t *func, macro_t *macro) {
    return blocks->add_block(blocks_idx, parent, func, macro);
}

void global_t::add_alias(const std::string &alias, const std::string &value) {
    aliases->add_alias(aliases_idx, alias, value);
    // INFO("alias = " + aliases->alias + " value = " + aliases->value + "  alidx = " + std::to_string(aliases_idx));
    info << "alias = " << aliases->alias << " value = " << aliases->value << "  alidx = " << std::to_string(aliases_idx);
}

func_t* global_t::add_func(const std::string &name) {
    return funcs->add_func(name, funcs_idx, func_tries, func_tries_idx);
}

void elf_t::elf_add_symbol(const std::string& symbol, int len, int pc) {
    elf_write_symbol_int(elf_strtab_index);
    elf_write_symbol_int(pc);
    elf_write_symbol_int(0);
    elf_write_symbol_int(pc == 0 ? 0 : 1 << 16);

    elf_strtab += symbol;
    elf_strtab_index += len;
    elf_strtab[elf_strtab_index++] = 0;
    elf_symbol_index++;
}

static char e_extract_byte(int v, int b) {
    return (v >> (b * 8)) & 0xFF;
}

int elf_t::elf_write_int(std::string &buf, int index, int val) {
    for (int i = 0; i < 4; i++) {
        buf[index++] = e_extract_byte(val, i);
        // INFO("index = " + std::to_string(index) + " val = " + std::to_string(val));
        info << "index = " << std::to_string(index) << " val = " << std::to_string(val);
    }
    printf("\n");
    return index;
}

void elf_t::elf_write_symbol_int(int val) {
    elf_symbol_index = elf_write_int(elf_symtab, elf_symtab_index, val);
    // INFO("symbol_index = " + std::to_string(elf_symbol_index));
    info << "symbol_index = " << std::to_string(elf_symbol_index);
}