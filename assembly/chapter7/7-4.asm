assume cs:codesg, ds:datasg

; 使用SI和DI实现将字符串存储到后面的内存中
; SI和DI与BX类似，但是SI、DI不可以分成两个8位寄存器

datasg segment
    db 'welcome to masm!'
    db '................'
datasg ends

codesg segment
start:
    mov ax, datasg
    mov ds, ax

    mov cx, 8 ; 为什么是8呢，因此一次会移动2个字节
    mov si, 0
    mov di, 16
s:
    mov ax, [si]
    mov [di], ax
    ; 注意，因为si、di都是16位寄存器，那么每次应该加2才能到达下一个字段
    add si, 2 
    add di, 2
    loop s

    mov ax, 4c00h
    int 21h
codesg ends

end start