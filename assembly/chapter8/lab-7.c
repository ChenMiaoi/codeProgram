#include <stdio.h>

int main() {
    char data[][21] = {
        { "1975", 1976, 1977, 1978, 1979, 1980, 1981, 1982, 1983, 1984, 1985, 1986, 1987, 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995 },
        { 16, 22, 382, 1356, 2390, 8000, 16000, 24486, 50065, 97479, 140417, 197514, 345980, 590827, 803530, 1183000, 1843000, 2759000, 3753000, 4649000, 5937000 },
        { 3, 7, 9, 13, 28, 38, 130, 220, 476, 778, 1001, 1442, 2258, 2793, 4037, 5635, 8226, 11542, 14430, 15257, 17800 }
    };
    char table[][16] = {
        "year summ ne ?? ", "year summ ne ?? ",
        "year summ ne ?? ", "year summ ne ?? ",
        "year summ ne ?? ", "year summ ne ?? ",
        "year summ ne ?? ", "year summ ne ?? ",
        "year summ ne ?? ", "year summ ne ?? ",
        "year summ ne ?? ", "year summ ne ?? ",
        "year summ ne ?? ", "year summ ne ?? ",
        "year summ ne ?? ", "year summ ne ?? ",
        "year summ ne ?? ", "year summ ne ?? ",
        "year summ ne ?? ", "year summ ne ?? ",
        "year summ ne ?? "
    };

    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 4; j++) {
            // table[i][j] = data[0][i][j];
        }
    }
    return 0;
}