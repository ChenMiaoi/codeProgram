#include <stdio.h>

int global_init = 0x11111111;
const int global_const = 0x22222222;

int main() 
{
	static int static_var = 0x33333333;
	static int static_var_uninit;

	int auto_var = 0x44444444;
	printf("hello world!\n");
	return 0;
}