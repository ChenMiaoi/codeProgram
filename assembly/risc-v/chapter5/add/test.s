# add
# Format:
#       ADD RD, RS1, RS2

    .text               # define beginning of text section
    .global _start      # define entry _start

_start:
    li x6, 1            # x6 = 1
    li x7, 2            # x7 = 2
    add x5, x6, x7      # x5 = x6 + x7
    
stop:
    j stop              # infinite loop to stop execution

    .end                # end of file
