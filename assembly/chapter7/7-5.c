#include <stdio.h>

int main() {
    char datasg[][16] = {
        "1. file         ",
        "2. edit         ",
        "3. search       ",
        "4. view         ",
        "5. options      ",
        "6. help         "
    };
    for (int i = 0; i < 6; i++) { // 此处的temp是为了和汇编保持一致
        char temp = datasg[i][3];
        temp &= 0xDF;
        datasg[i][3] = temp;
    }
    return 0;
}
