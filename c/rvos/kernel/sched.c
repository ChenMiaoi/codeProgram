#include "os.h"
#include "sched.h"

/*定义在swicth.S中 */
extern void __switch_to(context_t* next);

#define MAX_TASK 10
#define STACK_SIZE (1 << 10)

/**
 * 值得注意的是，在RISCV中，sp指针是16位字节对齐的
 */
uint8_t __attribute__((aligned(16))) task_stack[MAX_TASK][STACK_SIZE];
context_t ctx_tasks[MAX_TASK];

/* `_top` 用于标记ctx_tasks的最大可用位置 */
static int _top = 0;
/* `_current` 用于标记当前任务的上下文 */
static int _current = -1;

/**
 * 调度的初始化程序
 * 在switch.S中我们就知道，需要对mscratch进行置零操作
 */
void sched_init(void) {
    w_mscratch(0);
}

void schedule() {
    if (_top <= 0) {
        panic("Num of task should be greater than zero!");
        return;
    }

    /* 对下一个程序进行调度 */
    _current = (_current + 1) % _top;
    context_t* next = &(ctx_tasks[_current]);
    __switch_to(next);
}

/**
 * 执行一个简答的FIFO调度算法
 *  
 * @param start_routin 
 * @return int 
 */
int task_create(void (*start_routin)(void)) {
    if (_top < MAX_TASK) {
        /* 此处设置运行栈和调度切换时要运行的任务 */
        ctx_tasks[_top].sp = (reg_t)&task_stack[_top][STACK_SIZE];
        ctx_tasks[_top].ra = (reg_t)start_routin;
        _top++;
        return 0;
    }
    return -1;
}

/**
 * 当前任务自主放弃CPU资源，进行调度
 */
void task_yield() {
    schedule();
}

/**
 * 一个简单的任务，用于测试CPU调度
 */
void task_delay(volatile int count) {
    count *= 50000;
    while (count--);
}

