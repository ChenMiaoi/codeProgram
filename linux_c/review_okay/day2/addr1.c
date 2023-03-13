#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int un_gal = 100;

int main() {
    pid_t id = fork();

    if (id < 0) {
        perror("exit");
        _exit(0);
    } else if (id == 0) {
        int cnt = 0;
        while (1) {
            printf("I am child, pid: %d, ppid: %d, un_gal: %p, un_gal_val: %d\n",\
                    getpid(), getppid(), &un_gal, un_gal);
            if (cnt++ == 5) {
                printf("child change un_gal 100 -> 200, success\n");
                un_gal = 200;
            }
            sleep(1);
        }
    } else {
        while (1) {
            printf("I am father, pid: %d, ppid: %d, un_gal: %p, un_gal_val: %d\n",\
                    getpid(), getppid(), &un_gal, un_gal);
            sleep(1);
        }
    }
    return 0;
}