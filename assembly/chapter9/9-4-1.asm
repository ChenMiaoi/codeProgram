; 若要使程序中的jmp指令执行后，CS：IP指向程序的第一条指令，在data段中应该定义哪些数据

; jmp word ptr 内存单元地址(段内转移)
; 功能：从内存单元地址处开始存放一个字，是转移的目的偏移地址

; mov ax, 0123h
; mov ds:[0], ax
; jmp word ptr ds:[0]
; 执行后：IP = 0123H

; jmp dword ptr 内存单元地址(段间转移)
; 功能：从内存单元地址处开始存放两个字，高地址是段地址，低地址是偏移地址

; mov ax, 0123h
; mov ds:[0], ax
; mov word ptr ds:[2], 0
; jmp dword ptr ds:[0]
; 执行后：CS = 0000, IP = 0123H

assume cs:codesg

data segment
    db 0, 0 ; 如果要使jmp word ptr [bx + 1]跳转到cs:0000，那么说明至少data:0001的数据是0
data ends

codesg segment
start:
    mov ax, data
    mov ds, ax
    mov bx, 0
    jmp word ptr [bx + 1]

    mov ax, 4c00h
    int 21h
codesg ends

end start