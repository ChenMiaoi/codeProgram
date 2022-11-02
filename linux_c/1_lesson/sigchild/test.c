#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int sig)
{
	printf("pid : %lu, get a sig : %d\n", getpid(), sig);
}

int main()
{
	signal(SIGCHLD, handler);
	if (0 == fork()){
		printf("child running....pid : %lu, ppid : %lu\n", getpid(), getppid());
		sleep(5);
		printf("child quit!\n");
		exit(1);
	}
	while (1);
}
