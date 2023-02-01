assume cs:codesg

codesg segment
start:
    mov ax, 2000h
    mov ds, ax
    mov bx, 1000h
    mov word ptr [bx], 00BEh
    mov word ptr [bx + 2], 0006h

    mov ax, 2000h
    mov es, ax
    jmp dword ptr es:[1000h]

    mov ax, 4c00h
    int 21h
codesg ends

end start

; 以上程序执行后，CS = ？，IP = ？
; CS = 0006H，IP = 00BEH