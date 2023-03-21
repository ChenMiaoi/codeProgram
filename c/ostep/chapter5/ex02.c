/**
 * 编写一个打开文件的程序（使用 open()系统调用），然后调用 fork()创建一个新进程。
 * 子进程和父进程都可以访问 open()返回的文件描述符吗？当它我并发（即同谁）写入文件时，会发生什么？
*/

// 都可以访问同一个文件描述符，并发写入时，写入顺序是未知的

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main() 
{
    int fd;
    pid_t pid;
    fd = open("../ex02.txt", O_CREAT | O_RDWR | O_APPEND);
    pid = fork();
    if (pid == 0) {
        printf("fd: %d\n", fd);
        // fprintf(fd, "child write\n");
        write(fd, "child write\n", 12);
        printf("child write done!\n");
    }else if (pid > 0) {
        printf("fd: %d\n", fd);
        // fprintf(fd, "parent write\n");
        write(fd, "parent write\n", 12);
        printf("parent write done!\n");
    }
    close(fd);
    return 0;
}