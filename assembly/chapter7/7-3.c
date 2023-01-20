#include <stdio.h>

int main() {
    char a[5] = "BaSiC";
    char b[5] = "MinIX";
    int i = 0;
    do
    {
        a[i] = a[i] & 0xDF;
        b[i] = b[i] | 0x20;
    } while (i++ < 5);
    
    return 0;
}
