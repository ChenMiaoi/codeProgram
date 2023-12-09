#include "os.h"

void __main__(void) {
    uart_init();
    page_init();

    while (1) ;
}
