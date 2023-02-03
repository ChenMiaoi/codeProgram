; call 16位reg
; sp = sp - 2
; (ss * 16 + sp) = IP
; IP = reg
; 其实际相当于：
    ; push IP
    ; jmp reg

; 下面的程序执行完毕后，ax的值是多少
内存地址          机器码          汇编指令
1000:0          b8 06 00        mov ax, 6
1000:3          ff d0           call ax
1000:5          40              inc ax
1000:6                          mov bp, sp
                                add ax, [bp]
; call ax执行，此时CS:IP = 1000:5，且push IP，CS:IP = 1000:6
; mov bp, sp
; add ax, [bp] 默认段地址是ss:[bp] = ss:[sp] = 6
; 则 ax = ax + 6 = 11 = BH