#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Hello world");
    sleep(1);
    exit(1);
    _exit(1);
    return 0;
}