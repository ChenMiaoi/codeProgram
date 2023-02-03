; call far ptr 标号，实现的是段间转移
; sp = sp - 2
; (ss * 16 + sp) = CS
; sp = sp - 2
; (ss * 16 + sp) = IP
; CS = 标号的段地址
; IP = 标号的偏移地址
; 其实际相当于执行：
    ; push CS
    ; push IP
    ; jmp far ptr 标号

; 下面的程序执行完毕后，ax的值是多少
内存地址          机器码          汇编指令
1000:0          b8 00 00        mov ax, 0
1000:3          9a 09 00 00 10  call far ptr s
1000:8          40              inc ax
1000:9          58            s:pop ax
                                add ax, ax
                                pop bx
                                add ax, bx
; 执行call far ptr s语句时，CS:IP = 1000：8，也就是说
; pop ax = 8          
; add ax, ax = 10h
; pop bx = 1000h
; add ax, bx = 1010h