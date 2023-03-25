# addi
# Format:
#       ADDI RD, RS, %imm

    .text
    .global _start

_start:
    li x6, 6            # x6 = 6
    addi x5, x6, -7;    # x5 = x6 + -7
    
stop:
    j stop

    .end
