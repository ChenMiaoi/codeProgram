#include "./platform.h"

    # 设置每一个hart流的栈大小都为1024bytes
    .equ STACK_SIZE, 1024
    .text
    .global _start

_start:
    csrr    t0, mhartid     # 读取现在的hart id号
    mv      tp, t0
    bnez    t0, sleep       # 我们只允许一个hart流运行，其余hart流则休眠

    # 初始化.bss段
    la      a0, _bss_start
    la      a1, _bss_end
    bgeu    a0, a1, 2f

1:
    # 如果栈的结构是 栈底在低字节，栈顶在高字节
    # 那么直接从栈底(_bss_start)开始进行初始化操作
    sw      zero, (a0)
    addi    a0, a0, 4;
    bltu    a0, a1, 1b      # 如果bss_start < bss_end就说明没有到达栈顶

2:
    # 如果栈的结构是 栈顶在低字节，栈底在高字节
    slli    t0, t0, 10
    la      sp, stacks + STACK_SIZE
                            # 我们需要重新初始化栈指针位置
    add     sp, sp, t0;     # 使得不论哪一种结构，sp的指向始终从栈底开始
    
    j main                  # jump to main
    
sleep:
    wfi
    j       sleep           # jump to    sleep      

stacks:
    # 为所有的hart流开辟一个栈空间
    .skip   STACK_SIZE * MAXNUM_CPU

    .end
