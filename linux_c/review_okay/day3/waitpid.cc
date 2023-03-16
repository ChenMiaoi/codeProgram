#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef void (*handler_t)();

std::vector<handler_t> handlers;

void func_one() {
    printf("这是任务调用1\n");
}

void func_two() {
    printf("这是任务调用2\n");
}

void load() {
    handlers.push_back(func_one);
    handlers.push_back(func_two);
}

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
        int quit = 0;
        while (!quit) {
            int status = 0;
            pid_t ref = waitpid(-1, &status, WNOHANG);
            if (ref > 0) {
                printf("等待子程序退出成功， 退出码: %d\n", WEXITSTATUS(status));
                quit = 1;
            } else if (ref == 0) {
                printf("子进程还在运行中，父进程非阻塞等待\n");
                if (handlers.empty()) load();
                for (const auto& i : handlers) {
                    printf("执行其他任务\n");
                    i();
                }
            } else {
                printf("等待失败\n");
                quit = 1;
            }
        }
        // printf("I am father, pid: %d, ppid: %d\n", getpid(), getppid());
        // int ref_status = 0;
        // pid_t ref = waitpid(id, &ref_status, 0);
        // if (ref > 0) {
        //     // printf("wait success, pid: %d, child recv code: %d, the status: %d, means: %s\n", \
        //     //     ref, ref_status & 0x7F, ref_status >> 8 & 0xFF, strerror(ref_status >> 8 & 0xFF));
        //     if (WIFEXITED(ref_status)) {
        //         printf("normal exit, the status code: %d, means: %s\n", WEXITSTATUS(ref_status), strerror(WEXITSTATUS(ref_status)));
        //     }else {
        //         printf("exception exit, the status code: %d, means: %s\n", WEXITSTATUS(ref_status), strerror(WEXITSTATUS(ref_status)));
        //     }
        // }
    }
    return 0;
}