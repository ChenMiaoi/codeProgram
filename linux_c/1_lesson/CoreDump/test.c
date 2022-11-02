#include <stdio.h>
#include <unistd.h>

/*
 * ulimit -a查看系统文件上限指标
 * core dumped转储存在(默认)当前目录:名字后面跟着的数字代表的是你的进程编号
 * core_file不是给人看的，而是给调试器看的，在gdb里面直接core-file core_file就可以看见了
 * 好处是：能够直接找到问题所在
 * 坏处是：core dump会导致磁盘增大，同时一个服务挂了，第一时间应该是解决重启操作
 * */
int main()
{
	printf("get pid :> %d\n", getpid());
	int i = 0;
	int arr[100];
	for (; i < 200; i++)
		arr[i] = i;
	printf("run hear?\n");
	return 0;
}
