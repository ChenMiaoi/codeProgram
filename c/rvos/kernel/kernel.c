#include "os.h"

extern void page_test();
extern void os_main();

int main(void) {
    uart_init();
    page_init();

    page_test();

    sched_init();

    os_main();

    schedule();

    while (1) ;
}
