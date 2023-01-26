; 编程，将每一行都改为大写字母
assume cs:codesg, ds:datasg

datasg segment
    db 'ibm             '
    db 'dec             '
    db 'dos             '
    db 'vax             '
datasg ends

codesg segment
start:
    mov ax, datasg
    mov ds, ax

    mov bx, 0
    mov cx, 4 ; 有多少行
s0:
    mov dx, cx ; 将外层循环的值保存在dx中
    mov cx, 3 ; 有多少个字母需要改写，内层循环
    mov si, 0
    s1:
        mov al, [bx + si]
        and al, 11011111B
        mov [bx][si], al
        inc si
        loop s1
    add bx, 16 ; 换下一行
    mov cx, dx ; 取出外层循环的值，这样的操作会避免内存循环计数器和外层混杂
    loop s0

    mov ax, 4c00h
    int 21h
codesg ends

end start