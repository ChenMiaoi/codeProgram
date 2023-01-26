#include <stdio.h>

int main() {
    char datasg[][16] = {
        "ibm             ",
        "dec             ",
        "dos             ",
        "vax             "
    };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            char temp = datasg[i][j];
            temp &= 0xDF;
            datasg[i][j] = temp;
        }
    }
    return 0;
}