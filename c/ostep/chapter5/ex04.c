/**
 * 编写一个调用 fork()的程序，然后调用某种形式的 exec()来运行程序/bin/ls。
 * 看看是否可以尝试 exec()的所有变体，包括 
 * execl()、execle()、execlp()、execv()、execvp()和 execvpe()
 * 为什么同样的基本调用会有这么多变种？
*/

// exec*系列函数都是基于同一个system call -> execve

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[], char* env[])
{
    execl("/usr/bin/ls", "ls", "-a", "-l", NULL);
    execlp("ls", "ls", "-a", "-l", NULL);
    execle("/usr/bin/ls", "ls", "-a", "-l", NULL, env);
    argv[1] = "-a";
    argv[2] = "-l";
    argv[3] = NULL;
    execv("/usr/bin/ls", argv);
    execvp("ls", argv);
    execvpe("ls", argv, env);
    _exit(0);
}