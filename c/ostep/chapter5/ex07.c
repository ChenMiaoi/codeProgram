/**
 * 编写一个创建子进程的程序，然后在子进程中关闭标准输出（STDOUT_FILENO）。
 * 如果子进程在关闭描述符后调用 printf()打印输出，会发生什么？
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// 结果就是无法进行有效输出

int main() 
{
    pid_t id;
    id = fork();
    if (id == 0) {
        printf("close STDOUT_FILENO\n");
        close(STDOUT_FILENO);
        printf("Hello World");
    } else {
        wait(0);
    }
    return 0;
}