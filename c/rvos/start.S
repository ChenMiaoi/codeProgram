#include "./platform.h"

    # 设置每一个hart流的栈大小都为1024bytes
    .equ STACK_SIZE, 1024
    .text
    .global _start

_start:
    csrr    t0, mhartid     # 读取现在的hart id号
    mv      tp, t0
    bnez    t0, sleep       # 我们只允许一个hart流运行，其余hart流则休眠

    slli    t0, t0, 10      # 为栈的开辟留出空间，1024 = 1 << 10
    # 设置栈指针
    la      sp, stacks + STACK_SIZE
    add     sp, sp, t0;     # 将栈指针移动到预先留出的位置处

    j       __main__        # 跳转到C函数

sleep:
    wfi
    j       sleep           # jump to    sleep      

stacks:
    # 为所有的hart流开辟一个栈空间
    .skip   STACK_SIZE * MAXNUM_CPU

    .end
