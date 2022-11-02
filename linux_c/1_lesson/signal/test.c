#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void show_pending(sigset_t* pending)
{
	int sig = 1;
	for (; sig <= 31; sig++){
		if (sigismember(pending, sig)){
			printf("1 ");
		}
		else{
			printf("0 ");
		}
	}
	printf("\n");
}

void handler(int sig)
{
	printf("get a sig :> %d\n", sig);
}

int main()
{
	signal(2, handler);
	sigset_t pending;
	sigset_t block, oblock;
	sigemptyset(&block);
	sigemptyset(&oblock);

	sigaddset(&block, 2); //这个操作没有实现进操作系统，仍然在用户空间
	
	//真正的设置是sigprocmask
	sigprocmask(SIG_SETMASK, &block, &oblock);

	int count = 0;
	while (1){
		sigemptyset(&pending);
		sigpending(&pending);
		show_pending(&pending);
		sleep(1);
		count++;
		if (count == 10){
			printf("recover sig mask!\n");
			sigprocmask(SIG_SETMASK, &oblock, NULL);
		}
	}
	return 0;
}
