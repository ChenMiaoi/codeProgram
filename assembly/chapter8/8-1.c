#include <stdio.h>

typedef struct company {
    char cn[3];     // 公司名称
    char hn[9];     // 总裁姓名
    int pm;         // 排   名
    int sr;         // 收   入
    char cp[3];     // 著名产品
}company;

company dec = {"DEC", "Ken Olsen", 137, 40, "PDP"};

int main() {
    dec.pm = 38;
    dec.sr = dec.sr + 70;
    int i = 0;
    dec.cp[i] = 'V';
    i = i + 1;
    dec.cp[i] = 'A';
    i = i + 1;
    dec.cp[i] = 'X';
    return 0;
}