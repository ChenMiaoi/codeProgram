# not
# Format:
#       NOT RD, RS

    .text
    .global _start

_start:
    li x6, 0x10 # x6 = 0x10
    not x5, x6

    xori x5, x5, -1
    # 这就是not的底层指令

stop:
    j stop

    .end
