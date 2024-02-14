#include "os.h"
#include "platform.h"
#include "riscv.h"
#include "sched.h"
#include "types.h"

/* 为了方便，将trap_vector定义在switch.S中 */
extern void trap_vector(void);

void trap_init(void) {
    w_mtvec((reg_t)trap_vector);
}

void external_interrupt() {
    int irq = plic_claim();

    if (irq == UART0_IRQ) {
        uart_isr();
    } else if (irq)
        printf("unexpected interrupt irq = %d\n", irq);

    if (irq) 
        plic_complete(irq);
}

/**
 * 这是一个极其简单的用例，实话讲，我觉得很丑陋，只是为了测试trap是否可行
 */
reg_t trap_handler(reg_t epc, reg_t cause, context_t* ctx) {
    reg_t return_pc = epc;
    reg_t cause_code = cause & 0xFFF;
    
    printf("cause: %x\n", cause);
    printf("cause_code: %x\n", cause_code);

    if (cause & 0x80000000) {
        switch (cause_code) {
        case 3:
            printf("software interruption!\n");

            /**
             * 允许MSIP清空软件中断
             */
            int id = r_mhartid();
            *(uint32_t*)CLINT_MSIP(id) = 0;

            schedule();

            break;
        case 7:
            printf("timer interruption!\n");
        #ifdef TIMER_TEST
            timer_handler();
        #endif
            break;
        case 11:
            printf("external interruption!\n");
        #ifdef EX_IER_TEST
            external_interrupt();
        #endif
            break;
        default:
            panic("unknown async exception!");
            break;
        }
    } else {
        printf("Sync exceptions!, code = %d\n", cause_code);
        switch (cause_code) {
		case 8:
			uart_puts("System call from U-mode!\n");
			// do_syscall(ctx);
			return_pc += 4;
			break;
		default:
			panic("OOPS! What can I do!");
			//return_pc += 4;
		}
    }

    return return_pc;
}

void trap_test() {
    /*
	 * Synchronous exception code = 7
	 * Store/AMO access fault
	 */
	*(int *)0x00000000 = 100;

	/*
	 * Synchronous exception code = 5
	 * Load access fault
	 */
	// int a = *(int *)0x00000000;

	printf("Yeah! I'm return back from trap!\n");
}