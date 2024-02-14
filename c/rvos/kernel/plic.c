/**
 * ref https://github.com/riscv/riscv-plic-spec/blob/master/images/PLICArch.jpg
 * Riscv官方提供的一个板级中断示例
 */

#include "os.h"
#include "platform.h"
#include "riscv.h"

void plic_init() {
    int hart = r_tp();

    /**
     * 对UART0中断例程设置优先级
     * 
     * 每一个PLIC中断源都能够设置其独立的中断优先级寄存器
     * 对于QEMU中模拟的PLIC支持7个优先级，优先级的值从0~7
     * 优先级0被作为保留号
     * 优先级1~7分别是从最低到最高，如果有两个优先级相同的中断例程，
     * 那么比较其中断号高低，中断号越低，优先级越高
     */
    *(uint32_t*)PLIC_PRIORIY(UART0_IRQ) = 1;

    /**
     * 对UART0的中断使能
     * 
     * 设置UART0_IRQ的中断位是否使能
     */
    *(uint32_t*)PLIC_MENABLE(hart) = (1 << UART0_IRQ);

    /**
     * 设置UART0中断优先级阈值
     * 
     * PLIC可以设置一个阈值，使得低于阈值的中断优先级例程不使能
     */
    *(uint32_t*)PLIC_MTHRESHOLD(hart) = 0;

    /* 启动rv架构中，M级的允许外部中断 */
    w_mie(r_mie() | MIE_MEIE);

    /* 允许全局中断 */
    // w_mstatus(r_mstatus() | MSTATUS_MIE);
}

/**
 * 对PLIC进行检查是否当前有中断例程正在服务

 * 如果成功的调用了claim，会原子地清除中断源上的挂起位
 * 
 * @return int 返回最高优先级挂起中断的id，如果没有例程则返回0
 */
int plic_claim(void) {
    int hart = r_tp();
    int irq  = *(uint32_t*)PLIC_MCLAIM(hart);
    return irq;
}

/**
 *  通知PLIC该irq中断例程应当处理完成
 *
 *! 值得注意的是，PLIC在调用COMPLETE时不会检查该irq与调用最后声明的irq是否相同
 *  如果完成irq与当前中断源例程不匹配，则默认忽略此完成
 */
void plic_complete(int irq) {
    int hart = r_tp();
    *(uint32_t*)PLIC_MCOMPLETE(hart) = irq;
}