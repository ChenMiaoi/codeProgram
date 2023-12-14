#include "os.h"
#include "platform.h"
#include "riscv.h"

/* 设置间隔约等于一秒 */
#define TIMER_INTERVAL CLINT_TIMEBASE_FREQ

static uint32_t _tick = 0;

/**
 * 为每次定时器中断载入一个间隔时间
 * 
 * @param interval 间隔时间
 */
void timer_load(int interval) {
    /* 对于每个核心，都有自己独立的定时器资源 */
    int id = r_mhartid();
    /* 设置TIME_CMP, 如果TIME_CMP > TIME就会发生一次中断 */
    *(uint64_t*)CLINT_MTIME_CMP(id) = *(uint64_t*)CLINT_MTIME + interval;
}

/**
 * 定时器初始化函数
 */
void timer_init() {
    /**
     * 在重置定时器时，由于mtime会自动重装为0，而mtimecmp不会，所以我们需要手动的
     * 重装mtimecmp为0
     */
    timer_load(TIMER_INTERVAL);

    /* 允许定时器中断 */
    w_mie(r_mie() | MIE_MTIE);

    /* 允许全局中断 */
    w_mstatus(r_mstatus() | MSTATUS_MIE);
}

/**
 * 测试定时器中断
 */
void timer_handler() {
    _tick++;
    printf("tick: %d\n", _tick);

    timer_load(TIMER_INTERVAL);
}