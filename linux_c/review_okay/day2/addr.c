#include <stdio.h>
#include <stdlib.h>

int un_gal_var;
int gal_var = 100;

int main(int argc, char* argv[], char* env[]) {
    printf("text: %p\n", main);
    printf("init: %p\n", &gal_var);
    printf("uninit: %p\n", &un_gal_var);

    int* p = (int*)malloc(10);
    printf("heap: %p\n", p);
    printf("stack: %p\n", &p);
    for (int i = 0; i < argc; i++) { 
        printf("argv[%d]: %p\n", i, argv[i]);
    }
    for (int i = 0; env[i]; i++) {
        printf("env[%d]: %p\n", i, env[i]);
    }
    return 0;
}       