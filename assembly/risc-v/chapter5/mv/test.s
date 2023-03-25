# mv
# Format:
#       MV RD, RS

    .text
    .global _start

_start:
    li x6, 30           # x6 = 30
    mv  x5, x6          # x5 = x6
    addi x5, x6, 0;     # x5 = x6 + 0  
    # mv是一条伪指令，其内部汇编为addi rd, rs1, 0
    
stop:
    j stop

    .end
