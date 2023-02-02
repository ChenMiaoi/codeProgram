; 编译器对转移位移越界的检测

assume cs:codesg

codesg segment
start:
    jmp short s ; Jump out of range by 1 byte(s)
    db 128 dup (0)
s:
    mov ax, 0ffffh

    mov ax, 4c00h
    int 21h
codesg ends 

end start