#include <stdio.h>
#include <unistd.h>

int main() {
    printf("程序开始...\n");
    execl("/usr/bin/ls", "ls", "-a", NULL);
    printf("程序结束...\n");
    return 0;
}