#include <cstdio>
#include <cstring>

#include "symbol/global.h"
#include "symbol/parse.h"
#include "../config"

int main(int argc, char* argv[]) {
    int libc = 1;
    char* out = nullptr, *in = nullptr;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            printf("Usage: shecc <Option> file\n\n");
            printf("Option:\n");
            printf("\t-o, output\tfor rename binary name\n");
            printf("\t    --dump-ir\tgenerate IR code\n");
            printf("\t    --no-libc\tno need libc\n");
            return 0;
        }
        if (!strcmp(argv[i], "--dump-ir"))
            // TODO
            printf("dump-ip\n");
        else if (!strcmp(argv[i], "--no-libc"))
            libc = 0;
        else if (!strcmp(argv[i], "-o")) {
            if (i < argc + 1) {
                out = argv[i + 1];
                i = i + 1;
            } else {
                // TODO 
            }
        } else {
            in = argv[i];
        }
    }

    if (!in) {
        ERROR("Missing source file!");
        return -1;
    }
    if (libc) {

    }
    global_init();

    parse parse(in);
    parse.run();
    return 0;
}