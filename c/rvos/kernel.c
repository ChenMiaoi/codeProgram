#include "os.h"

extern void page_test();

void __main__(void) {
    uart_init();
    page_init();

    page_test();

    while (1) ;
}
