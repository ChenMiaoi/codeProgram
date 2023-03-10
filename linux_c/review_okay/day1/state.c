#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main () {
    while (1) {
        /**
         * ! 如果只是空循环，状态为R，如果有IO输出，因为IO耗费的时间占比重，因此很多时候都在等待IO，因此是S状态
        */
        printf("hello world\n");
    }
}