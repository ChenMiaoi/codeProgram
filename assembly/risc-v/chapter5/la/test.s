# Load Address
# Format:
#       LA RD, Address

    .text
    .global _start

_start:
    la x5, _start       # 
    jr x5               # jump to x5
    
    .end
