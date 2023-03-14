#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
            // int a = 0;
            // a = 10 / a;
        }
        exit(20);
    } else {
        printf("I am father, pid: %d, ppid: %d\n", getpid(), getppid());
        int ref_status = 0;
        pid_t ref = waitpid(id, &ref_status, 0);
        if (ref > 0) {
            // printf("wait success, pid: %d, child recv code: %d, the status: %d, means: %s\n", \
            //     ref, ref_status & 0x7F, ref_status >> 8 & 0xFF, strerror(ref_status >> 8 & 0xFF));
            if (WIFEXITED(ref_status)) {
                printf("normal exit, the status code: %d, means: %s\n", WEXITSTATUS(ref_status), strerror(WEXITSTATUS(ref_status)));
            }else {
                printf("exception exit, the status code: %d, means: %s\n", WEXITSTATUS(ref_status), strerror(WEXITSTATUS(ref_status)));
            }
        }
    }
    return 0;
}