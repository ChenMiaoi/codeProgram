#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t id = fork();
    if (id < 0) {
        perror("fork");
        exit(1);
    } else if (id == 0) {
        int cnt = 5;
        while (cnt--) {
            printf("cnt: %d, I am child, pid: %d, ppid: %d\n", cnt, getpid(), getppid());
            sleep(1);
        }
    } else {
        printf("I am father, pid: %d, ppid: %d\n", getpid(), getppid());
        pid_t ref = wait(NULL);
        if (ref > 0) {
            printf("wait success, pid: %d\n", ref);
        }
        // while (1) {
        //     printf("I am father, pid: %d, ppid: %d\n", getpid(), getppid());
        //     sleep(1);
        // }
    }
    return 0;
}