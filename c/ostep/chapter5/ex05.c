/**
 * 现在编写一个程序，在父进程中使用 wait()，等待子进程完成。wait()返回什么？
 * 如果你在子进程中使用 wait()会发生什么？
*/

// wait会返回等到到的子进程pid。在子程序中调用wait会失败

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() 
{
    pid_t id;
    id = fork();
    if (id == 0) {
        pid_t ref;
        printf("child done, pid: %d\n", getpid());
        ref = wait(0);
        printf("the child wait: %d\n", ref);
        _exit(0);
    } else if (id > 0) {
        pid_t ref;
        ref = wait(0);
        printf("parent wait, the wait pid: %d\n", ref);
    }
    return 0;
}