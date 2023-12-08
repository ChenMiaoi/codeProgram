extern void uart_init(void);
extern void uart_puts(char* s);

void __main__(void) {
    uart_init();
    uart_puts("hello world\n");

    while (1) ;
}
