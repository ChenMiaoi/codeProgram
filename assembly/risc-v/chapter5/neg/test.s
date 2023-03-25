# neg
# Format:
#       NEG RD, RS

    .text
    .global _start

_start:
    li x6, 1            # x6 = 1
    neg x5, x6
    sub x5, x0, x6      # x5 = x0 - x6
    # neg是伪指令，其内部汇编代码就是 sub rd, 0, rs2

stop:
    j stop

    .end
