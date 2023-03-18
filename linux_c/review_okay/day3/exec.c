#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    pid_t id = fork();
    if (id == 0) {
        printf("child process start, pid: %d\n", getpid());
        execl("/usr/bin/ls", "ls", "-a", "-l", NULL);
        exit(0);
    }else {
        printf("parent process start, pid: %d\n", getpid());
        int status = 0;
        pid_t id = waitpid(-1, &status, 0);
        if (id > 0) 
            printf("wait success, exit code: %d\n", WEXITSTATUS(status));
    }
    // printf("程序开始...\n");
    // execl("/usr/bin/ls", "ls", "-a", NULL);
    // printf("程序结束...\n");
    return 0;
}