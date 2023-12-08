#ifndef __OS_H
#define __OS_H

#include "types.h"
#include "platform.h"

/* uart.c */
extern int uart_init(void);
extern int uart_putc(char c);
extern int uart_puts(char* s);

/* printf.c */

/* memory.c */

#endif //! __OS_H
