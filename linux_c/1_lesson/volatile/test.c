#include <stdio.h>
#include <signal.h>

volatile int quit = 0;

void handler(int sig)
{
	quit = 1;
	printf("quit is already set to 1\n");
}

int main()
{
	signal(2, handler);
	while (!quit);
	printf("process quit!\n");
}
