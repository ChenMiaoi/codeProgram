#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    // ! pri = old_pri + nice
    while (1) {
        printf("Hello world, pid: %d\n", getpid());
        sleep(1);
    }
    return 0;
}