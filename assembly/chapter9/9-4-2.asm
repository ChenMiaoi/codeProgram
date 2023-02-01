; 补全程序，使jmp指令执行后，CS：IP指向程序的第一条指令
; 想指向第一条指令，那实际上就是CS：0000

assume cs:codesg

data segment
    dd 12345678h
data ends

codesg segment
start:
    mov ax, data
    mov ds, ax
    mov bx, 0
    ; *** YOUR CODE ***
    mov [bx], bx
    mov [bx + 2], cs
    ; *** END ***
    jmp dword ptr ds:[0]

    mov ax, 4c00h
    int 21h
codesg ends

end start