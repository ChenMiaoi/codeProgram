/**
 * 编写一个调用 fork()的程序。调用 fork()之前，让主进程访问一个变量（例如 x）并将其值设置为某个值（例如 100）。
 * 子进程中的变量有什么值？当子进程和父进程都改变x的值时，变量会发生什么？
*/

// 一开始父子进程中的值是一致的，但在修改后，父子进程中的值同一个变量表现出了不同的值

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() 
{
    int x;
    x = 100;
    pid_t id = fork();
    if (id == 0) {
        printf("child x: %d\n", x);
        x = 200;
        printf("child change x: %d\n", x);
    }else if (id > 0) {
        printf("parent x: %d\n", x);
        x = 300;
        printf("parent change x: %d\n", x);
    }
    return 0;
}