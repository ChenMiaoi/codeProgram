; 编程，将每一行都改为大写字母
assume cs:codesg, ds:datasg, ss:stacksg

datasg segment
    db 'ibm             '
    db 'dec             '
    db 'dos             '
    db 'vax             '
    dw 0
datasg ends

stacksg segment
    dw 0, 0, 0, 0, 0, 0, 0, 0
stacksg ends

; 然而实际上，我们通常使用栈来保存临时数据

codesg segment
start:
    mov ax, stacksg
    mov ss, ax
    mov sp, 16
    mov ax, datasg
    mov ds, ax

    mov bx, 0
    mov cx, 4 ; 有多少行
s0:
    push cx
    mov cx, 3 ; 有多少个字母需要改写，内层循环
    mov si, 0
    s1:
        mov al, [bx + si]
        and al, 11011111B
        mov [bx][si], al
        inc si
        loop s1
        
    add bx, 16 ; 换下一行
    pop cx
    loop s0

    mov ax, 4c00h
    int 21h
codesg ends

end start