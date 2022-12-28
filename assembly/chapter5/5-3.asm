; 计算ffff:0006单元中的数乘以3,结果存储在dx中

assume cs:codesg

codesg segment
    mov ax, 0ffffh
    ; 数据不能以字母开头，因此ffffh要改为0ffffh
    mov ds, ax
    mov bx, 6
    mov al, [bx]
    mov ah, 0
    mov dx, 0
    mov cx, 123
loops:
    add dx, ax 
    loop loops

    mov ax, 4c00h
    int 21h
codesg ends

end

; G + SA(偏移地址) = 直接跳转到 CS:SA，也就是说， CS：IP = CS：SA为止
; 在汇编语言第四版上中，P指令可以用于中断和执行循环，但是本环境不适用
