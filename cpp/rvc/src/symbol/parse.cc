#include "parse.h"
#include "global.h"

#include <cstdio>
#include <fstream>
#include <ios>
#include <string>

extern global_t global_config;
extern elf_t elf_config;

void parse::run() {
    load_source_file();
    parse_internal();

    // for (int i = 0; i < global_config.types_idx; i++) {
    //     INFO(global_config.types[i].type_name);
    // }
}

void __load_source_file(const std::string& file) {
    std::ifstream steam(file);
    // steam.open(file, std::ios::in | std::ios::binary);
    // INFO("entry " + file);
    info << "entry " << file;
    if (!steam.is_open()) {
        // ERROR("can't open this file <" + file + ">");
        fatal << "can't open this file <" << file << ">";
        return;
    }
    std::string buffer;
    while (std::getline(steam, buffer)) {
        if (!buffer.compare(0, 9, "#include ") && buffer[9] == '"') {
            std::string path = buffer.substr(0, buffer.find_last_of("/") + 1);
            path += buffer.substr(10, buffer.size() - 11);
            __load_source_file(path);
        } else {
            global_config.source += buffer;
            global_config.source_idx += buffer.size();
        }
    }
    steam.close();
}

void parse::load_source_file() {
    __load_source_file(this->file);
}

void parse::parse_internal() {
    type_t* type;
    func_t* fn;

    type = global_config.add_type_name("void", TYPE_VOID);
    type = global_config.add_type_name("char", TYPE_CHAR);
    type = global_config.add_type_name("int", TYPE_INT);

    static_cast<void>(global_config.add_block(nullptr, nullptr, nullptr));
    elf_config.elf_add_symbol("", 0, 0);

    global_config.add_alias(ARCH_PREDEFINED, "1");

    fn = global_config.add_func("__syscall");

    // INFO("func = " + fn->return_def.var_name);
    info << "func = " << fn->return_def.var_name;
    // INFO("func_tries_idx = " + std::to_string(global_config.func_tries_idx));
    info << "func_tries_idx = " << std::to_string(global_config.func_tries_idx);
}