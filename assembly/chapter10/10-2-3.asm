; call word ptr 内存单元地址
; 其实际相当于：
    ; push IP
    ; jmp word ptr 内存单元地址

mov sp, 10h
mov ax, 0123h
mov ds:[0], ax
call word ptr ds:[0]
; 执行后，IP = 0123H， sp = 0Eh

; call dword ptr 内存单元地址
; 其实际相当于：
    ; push CS
    ; push IP
    ; jmp dword ptr 内存单元地址

mov sp, 10h
mov ax, 0123h
mov ds:[0], ax`
mov word ptr ds:[2], 0
call dword ptr ds:[0]
; 执行后，CS = 0, IP = 0123H, sp = 0ch

