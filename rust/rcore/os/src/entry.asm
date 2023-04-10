    .section .text.entry
    .globl _start
_start:
    la sp, boot_stack_top   # 载入栈
    call start_main          # 调用程序入口

    .section .bss.stack
    .globl boot_stack_lower_bound

# 为程序分配了64K的大小
boot_stack_lower_bound:
    .space 4096 * 16
    .globl boot_stack_top   # 标识栈顶位置
boot_stack_top: