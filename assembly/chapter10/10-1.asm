; ret指令用栈中的数据修改IP的内容，从而实现近转移
; retf指令用栈中的数据修改CS和IP的内容，从而实现远转移

; *** CPU执行ret指令时，进行下面两步操作 *** 
; IP = ss * 16 + sp
; sp = sp + 2
; 使用汇编指令来解释，其实就相当于 pop IP

; *** CPU执行retf指令时，进行下面四步操作 ***
; IP = ss * 16 + sp
; sp = sp + 2
; CS = ss * 16 + sp
; sp = sp + 2
; 使用汇编指令来解释，其实就相当于 pop IP, pop CS

; 下面的程序，ret指令执行后，IP = 0， CS:IP指向代码段的第一条指令
assume cs:code

stack segment
    db 16 dup (0)
stack ends

code segment
    mov ax, 4c00h
    int 21h
start:
    mov ax, stack
    mov ss, ax
    mov sp, 16
    mov ax, 0
    push ax
    mov bx, 0
    ret
code ends

end start

; 下面的程序，retf指令执行后, CS:IP指向代码段的第一条指令
assume cs:code

stack segment
    db 16 dup (0)
stack ends

code segment
    mov ax, 4c00h
    int 21h
start:
    mov ax, stack
    mov ss, ax
    mov sp, 16
    mov ax, 0
    push cx
    push ax
    mov bx, 0
    retf
code ends

end start