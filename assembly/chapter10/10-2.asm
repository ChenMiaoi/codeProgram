; call指令，执行call会经过两步
; 将当前IP或CS：IP压入栈中
; 转移
; *** call不能实现短转移 ***

; call 标号
; sp = sp - 2
; (ss * 16 + sp) = IP 将IP压入栈中
; IP = IP + 16位位移 -> 通过标号计算得出
; 其实际相当于在进行：
    ; push IP
    ; jmp near ptr 标号

; 下面的程序执行完毕后，ax的值是多少
内存地址          机器码          汇编指令
1000:0          b8 00 00        mov ax, 0
1000:3          e8 01 00        call s
1000:6          40              inc ax  
1000:7          58            s:pop ax
; 显然，call时，push IP, 跳转到 s后，pop出IP，ax = IP(原) = 6
; 为什么不等于3，而是6呢，因为当执行到1000:3时，IP已经是6了，从机器码也可以看出，e8 0001，只位移一位