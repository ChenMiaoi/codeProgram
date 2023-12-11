#ifndef __OS_H
#define __OS_H

#include "types.h"
#include "platform.h"

#include <stddef.h>
#include <stdarg.h>

/* uart.c */
extern int uart_init(void);
extern int uart_putc(char c);
extern int uart_puts(char* s);

/* printf.c */
extern int  printf(const char* fmt, ...);
extern void panic(const char* s);

/* mm.c */
extern void  page_init(void);
extern void* page_alloc(int npages);
extern void  page_free(void* p);

/* sched.c */
#include "sched.h"
extern void sched_init(void);
extern void schedule(void);
extern int  task_create(void (*task)(void));
extern void task_delay(volatile int count);
extern void task_yield();

#endif //! __OS_H
