#ifndef __PLATFORM_H__
#define __PLATFORM_H__

/**
 * param MAXNUM_CPU 该平台支持的最大CPU数，也就是hart数为0~7
*/
#define MAXNUM_CPU 8 

/**
 * MemoryMap
 * see https://github.com/qemu/qemu/blob/master/hw/riscv/virt.c, virt_memmap[] 
 * 0x00001000 -- boot ROM, provided by qemu
 * 0x02000000 -- CLINT
 * 0x0C000000 -- PLIC
 * 0x10000000 -- UART0
 * 0x10001000 -- virtio disk
 * 0x80000000 -- boot ROM jumps here in machine mode, where we load our kernel
 */

/**
 * QEUM中在物理地址0x1000 0000~100存放UART0
 */
#define UART0 0x10000000L

/**
 * UART0_IRQ 中断源
 * ref https://github.com/qemu/qemu/blob/master/include/hw/riscv/virt.h
 */
#define UART0_IRQ 10

/**
 * 板级中断PLIC
 * ref https://github.com/qemu/qemu/blob/master/include/hw/riscv/virt.h
 * ref https://github.com/riscv/riscv-plic-spec/blob/master/riscv-plic-1.0.0.pdf
 * 
 * @code {.cc}
 * #define VIRT_PLIC_HART_CONFIG "MS"
 * #define VIRT_PLIC_NUM_SOURCES 127
 * #define VIRT_PLIC_NUM_PRIORITIES 7
 * #define VIRT_PLIC_PRIORITY_BASE 0x04
 * #define VIRT_PLIC_PENDING_BASE 0x1000
 * #define VIRT_PLIC_ENABLE_BASE 0x2000
 * #define VIRT_PLIC_ENABLE_STRIDE 0x80
 * #define VIRT_PLIC_CONTEXT_BASE 0x200000
 * #define VIRT_PLIC_CONTEXT_STRIDE 0x1000
 * #define VIRT_PLIC_SIZE(__num_context) \
 *     (VIRT_PLIC_CONTEXT_BASE + (__num_context) * VIRT_PLIC_CONTEXT_STRIDE)
 * @endcode
 */
#define PLIC_BASE 0x0c000000L
#define PLIC_PRIORIY(id)        (PLIC_BASE + (id) * 4)
#define PLIC_PENDING(id)        (PLIC_BASE + 0x1000 + ((id) / 32) * 4)
#define PLIC_MENABLE(hart)      (PLIC_BASE + 0x2000 + (hart) * 0x80)
#define PLIC_MTHRESHOLD(hart)   (PLIC_BASE + 0x200000 + (hart) * 0x1000)
#define PLIC_MCLAIM(hart)       (PLIC_BASE + 0x200004 + (hart) * 0x1000)
#define PLIC_MCOMPLETE(hart)    (PLIC_BASE + 0x200004 + (hart) + 0x1000)

/**
 * 在Qemu-virt模拟的板级硬件上，有一个CLINT(Core Local INTerruptor)模块与软件定时器
 * 中断有关
 * ref https://gitee.com/qemu/qemu/blob/master/include/hw/riscv/sifive_clint.h
 * 
 * @code {.cc}
 * enum {
 * 	SIFIVE_SIP_BASE     = 0x0,
 * 	SIFIVE_TIMECMP_BASE = 0x4000,
 * 	SIFIVE_TIME_BASE    = 0xBFF8
 * };
 *
 * enum {
 * 	SIFIVE_CLINT_TIMEBASE_FREQ = 10000000
 * };
 * @endcode
 */
#define CLINT_BASE 0x20000000L
#define CLINT_MSIP(hart) (CLINT_BASE + 4 * (hart))
#define CLINT_MTIME_CMP(hart) (CLINT_BASE + 0x4000 + 8 * (hart))
#define CLINT_MTIME (CLINT_BASE + 0xBFF8)

/* 10000000 ticks每秒 */
#define CLINT_TIMEBASE_FREQ 10000000

#endif // !__PLATFORM_H__
