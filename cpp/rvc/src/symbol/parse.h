#ifndef __PARSE_H__
#define __PARSE_H__

#include <string>
#include "../util/util.h"

struct parse {
    parse(const char* _file): file(_file) {}

    void run();
    void load_source_file();
    void parse_internal();

    std::string file;
};

#endif //! __PARSE_H__