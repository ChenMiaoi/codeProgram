; 使用多个段

assume cs:code, ds:data, ss:stack

data segment
    dw 0123h, 0456h, 0789h, 0abch, 0defh, 0fedh, 0cbah, 0987h ; 10h
data ends

stack segment
    dw  dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ; 20h
stack ends

code segment
start:
    mov ax, stack ; 此处将栈的位置获取，通过ax传递给ss
    mov ss, ax
    mov sp, 20h ; 设置栈顶指向stack:20h

    mov ax, data ; ds指向data段
    mov ds, ax

    mov bx, 0
    mov cx, 8
s:
    push [bx]
    add bx, 2
    loop s

    mov bx, 0
    mov cx, 8
s0:
    pop [bx]
    add bx, 2
    loop s0

    mov ax, 4c00h
    int 21h
code ends

end start