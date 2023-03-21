/**
 * 编写一个程序，创建两个子进程，并使用 pipe()系统调用，将一个子进程的标准输出连接到另一个子进程的标准输入
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() 
{
    pid_t id;
    int data_pipe[2];
    id = fork();
    pipe(data_pipe);
    if (id == 0) {
        close(data_pipe[0]);
        close(STDIN_FILENO);
        dup(data_pipe[1]);
        write(data_pipe[1], "hello world", 13);
        close(data_pipe[1]);
        _exit(0);
    }else {
        pid_t iid;
        iid = fork();
        if (iid == 0) {
            char buf[15];
            close(data_pipe[1]);
            close(STDOUT_FILENO);
            dup(data_pipe[0]);
            read(data_pipe[0], buf, 13);
            close(data_pipe[0]);
            buf[strlen(buf)] = 0;
            printf("recv data: %s\n", buf);
            _exit(0);
        }else{
            sleep(1);
            waitpid(-1, NULL, 0);
        }
        sleep(1);
        waitpid(-1, NULL, 0);
    }
    return 0;
}