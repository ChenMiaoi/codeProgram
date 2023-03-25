# nop
# Format:
#       NOP

    .text
    .global _start

_start:
    nop
    addi x0, x0, 0; # x0 = x0 + 0
    # nop是一条伪指令，其内部汇编为addi x0, x0, 0
