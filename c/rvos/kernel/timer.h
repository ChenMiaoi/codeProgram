#ifndef __TIMER_H
#define __TIMER_H

#include "types.h"

typedef struct timer {
	void (*func)(void *arg);
	void *arg;
	uint32_t timeout_tick;
} timer_t;

#endif //! __TIMER_H