#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t id = fork();

    if (id < 0) {
        perror("error");
        _exit(1);
    } else if (id == 0) {
        while (1) {
            printf("I am child, pid: %d, ppid: %d\n", getpid(), getppid());
            sleep(2);
        }
    } else {
        printf("I am father, pid: %d, ppid: %d\n", getpid(), getppid());
        sleep(3);
        _exit(0);
    }
    return 0;
}