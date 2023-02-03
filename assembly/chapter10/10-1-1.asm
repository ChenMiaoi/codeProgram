; 补全程序, 实现从内存1000：0000处开始执行指令
assume cs:code

stack segment
    db 16 dup (0)
stack ends

code segment
start:
    mov ax, stack
    mov ss, ax
    mov sp, 10h
    ; *** YOUR CODE ***
    mov ax, 1000h
    push ax
    mov ax, 0h
    push ax
    ; *** YOUR CODE ***
    retf
code ends

end start