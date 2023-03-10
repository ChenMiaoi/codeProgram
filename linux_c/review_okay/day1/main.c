#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("hello world\n");
    pid_t pid = fork();
    if (pid < 0) {
        perror("error fork");
        _exit(-1);
    } else if (pid > 0) {
        printf("It's parent\n");
    } else {
        printf("It's child\n");
    }
}