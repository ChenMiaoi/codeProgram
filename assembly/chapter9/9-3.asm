; jmp far ptr 标号，实现的是段间位移，又称为远位移
    ; CS = 标号所在的段地址， IP = 标号所在段的偏移地址
    ; far ptr指明了用标号的段地址和偏移地址修改CS和IP

assume cs:codesg

codesg segment
start:
    mov ax, 0
    mov bx, 0
    jmp far ptr s ; EA0B01B004 JMP 04B0:010B
    db 256 dup (0)
s:
    add ax, 1
    inc ax

    mov ax, 4c00h
    int 21h
codesg ends

end start

; jmp reg(16位)
; 相当于将IP = (16位)reg