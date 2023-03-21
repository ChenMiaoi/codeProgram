/**
 * 对前一个程序稍作修改，这次使用 waitpid()而不是 wait()。什么时候waitpid()会有用？
*/

// 子进程中无效，父进程中，将waitpid的pid参数设置为-1或是等待进程的pid即有效

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() 
{
    pid_t id;
    id = fork();
    if (id == 0) {
        pid_t ref;
        int status;
        printf("child done, pid: %d\n", getpid());
        ref = waitpid(-1, &status, 0);
        printf("the child wait: %d, status code: %d, it means: %s\n", 
            ref, WEXITSTATUS(status), strerror(WEXITSTATUS(status)));
        _exit(0);
    } else if (id > 0) {
        pid_t ref;
        int status;
        ref = waitpid(-1, &status, 0);
        printf("parent wait, the wait pid: %d, the status code: %d\n", ref, WEXITSTATUS(status));
    }
    return 0;
}