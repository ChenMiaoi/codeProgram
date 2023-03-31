# or
# Format:
#       OR RD, RS1, RS2

    .text
    .global _start

_start:
    li x6, 0x10 # x6 = 0x10
    li x7, 0x11 # x7 = 0x11
    or x5, x6, x7

stop:
    j stop

    .end
