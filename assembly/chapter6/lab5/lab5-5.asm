; 编写code段中的代码，用push指令将a段中的前八位字形数据，逆序存储到b段中

assume cs:code

a segment
    dw 1, 2, 3, 4, 5, 6, 7, 8, 9, 0ah, 0bh, 0ch, 0dh, 0eh, 0fh, 0ffh
a ends

b segment
    db 0, 0, 0, 0, 0, 0, 0, 0
b ends

code segment
start:
    mov ax, a
    mov ds, ax

    mov ax, b
    mov ss, ax
    mov sp, 16

    mov bx, 0
    mov cx, 8
s:
    push ds:[bx] ; 直接压入栈中就是逆序
    add bx, 2 ; 因为数据是字型数据，一个字型占据两个字节
    loop s

    mov ax, 4c00h
    int 21h
code ends

end start