#include "os.h"
#include "platform.h"
#include "riscv.h"

/* 设置间隔约等于一秒 */
#define TIMER_INTERVAL CLINT_TIMEBASE_FREQ

static uint32_t _tick = 0;
#define  MAX_TIMER 10
static struct timer timer_list[MAX_TIMER];

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
    struct timer *t = &(timer_list[0]);
	for (int i = 0; i < MAX_TIMER; i++) {
		t->func = NULL; /* use .func to flag if the item is used */
		t->arg = NULL;
		t++;
	}

    /**
     * 在重置定时器时，由于mtime会自动重装为0，而mtimecmp不会，所以我们需要手动的
     * 重装mtimecmp为0
     */
    timer_load(TIMER_INTERVAL);

    /* 允许定时器中断 */
    w_mie(r_mie() | MIE_MTIE);

    /* 允许全局中断 */
    // w_mstatus(r_mstatus() | MSTATUS_MIE);
}

struct timer *timer_create(void (*handler)(void *arg), void *arg, uint32_t timeout)
{
	/* TBD: params should be checked more, but now we just simplify this */
	if (NULL == handler || 0 == timeout) {
		return NULL;
	}

	/* use lock to protect the shared timer_list between multiple tasks */
	spin_lock();

	struct timer *t = &(timer_list[0]);
	for (int i = 0; i < MAX_TIMER; i++) {
		if (NULL == t->func) {
			break;
		}
		t++;
	}
	if (NULL != t->func) {
		spin_unlock();
		return NULL;
	}

	t->func = handler;
	t->arg = arg;
	t->timeout_tick = _tick + timeout;

	spin_unlock();

	return t;
}

void timer_delete(struct timer *timer)
{
	spin_lock();

	struct timer *t = &(timer_list[0]);
	for (int i = 0; i < MAX_TIMER; i++) {
		if (t == timer) {
			t->func = NULL;
			t->arg = NULL;
			break;
		}
		t++;
	}

	spin_unlock();
}

/* this routine should be called in interrupt context (interrupt is disabled) */
static inline void timer_check()
{
	struct timer *t = &(timer_list[0]);
	for (int i = 0; i < MAX_TIMER; i++) {
		if (NULL != t->func) {
			if (_tick >= t->timeout_tick) {
				t->func(t->arg);

				/* once time, just delete it after timeout */
				t->func = NULL;
				t->arg = NULL;

				break;
			}
		}
		t++;
	}
}

/**
 * 测试定时器中断
 */
void timer_handler() {
    _tick++;
    printf("tick: %d\n", _tick);

    timer_check();

    timer_load(TIMER_INTERVAL);

    schedule();
}