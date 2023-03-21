/**
 * 使用 fork()编写另一个程序。子进程应打印“hello”，父进程应打印“goodbye”。
 * 你应该尝试确保子进程始终先打印。你能否不在父进程调用 wait()而做到这一点呢？
*/

// 可以使用sleep来休眠父进程

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() 
{
    pid_t id;
    id = fork();
    if (id == 0) {
        // printf("hello");
        write(0, "hello", 6);
    } else if (id > 0) {
        sleep(1);
        // printf("goodbye");
        write(0, "goodbye", 8);
    }
    return 0;
}