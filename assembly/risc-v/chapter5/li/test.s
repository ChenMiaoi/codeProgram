# Load Immediate
# Format:
#       LI RD, IMM

    .text
    .global _start

_start:
    # 如果立即数的范围在[-2048, +2048)
    li x5, 0x80             # x5 = 0x80
    # 以下是等价汇编指令
    addi x5, x0, 0x80;      # x5 = x0 + 0x80
    
    # 如果立即数的范围不在[-2048, +2048)且最高符号位是0
    li x6, 0x12345001       # x6 = 0x12345001
    # 以下是等价汇编指令
    lui x6, 0x12345
    addi x6, x6, 0x001;     # x6 = x6 + 0x001
    
    # 如果立即数的范围不在[-2048, +2048)且最高符号位是1
    li x7, 0x12345FFF # x7 = 0x12345FFF
    # 以下是等价汇编指令
    lui x7, 0x12346
    addi x7, x7, -1; # x7 = x7 + -1

stop:
    j stop

    .end
