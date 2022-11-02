#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig)
{
	printf("get a sig : %d\n", sig);
}

int main()
{
	struct sigaction act, oact;
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(2, &act, &oact);

	while (1);
}
