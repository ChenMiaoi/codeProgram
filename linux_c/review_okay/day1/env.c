#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]) {
    printf("begin.......................\n");
    // for (int i = 0; env[i]; i++) {
    //     printf("env[%d]: %s\n", i, env[i]);
    // }

    // extern char** __environ;
    // for (int i = 0; __environ[i]; i++) {
    //     printf("env[%d]: %s\n", i, __environ[i]);
    // }

    printf("%s\n", getenv("PATH"));
    printf("end.......................\n");
    return 0;
}