#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    for (int i = 0; i < 150; i++) {
        printf("%d: %s\n", i, strerror(i));
    }
    _exit(1);
    return 0;
}