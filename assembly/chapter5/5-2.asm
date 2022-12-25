; loop指令
; CPU执行loop时，需要进行两步判断：
    ; 1. (cx) = (cx) - 1
    ; 2. if (cx) != 0 -> continue; else break;

; 因此：可以看见，我们一般在CX寄存器中存放循环次数

; 计算2^12

assume cs:loopsg

loopsg segment
    mov ax, 2
    mov cx, 11
s:
    add ax, ax ; 标号实际上标识了一个地址，且先进行了一次循环才进行了loop，所以mov cx, 11。相当do...while
    loop s

    mov ax, 4c00h
    int 21h
loopsg ends

end