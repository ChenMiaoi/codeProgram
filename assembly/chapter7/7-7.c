#include <stdio.h>

int main() {
    char datasg[][16] = {
        "1. display      ",
        "2. brows        ",
        "3. replace      ",
        "4. modify       "
    };
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j < 7; j++) {
            char temp = datasg[i][j];
            temp &= 0xDF;
            datasg[i][j] = temp;
        }
    }
    return 0;
}