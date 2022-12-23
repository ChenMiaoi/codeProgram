assume cs:codesg

; [BX]表示一个内存单元，偏移地址在BX中，也就是DS：BX
; 定义：()
    ; 使用()来表示一个寄存器或一个内存单元中的内容
    ; ()中的元素可以有三种类型：
        ; 1. 寄存器名
        ; 2. 段寄存器名
        ; 3. 内存单元物理地址

codesg segment
    mov ax, 2000h
    mov ds, ax
    mov bx, 1000h
    mov ax, [bx]
    inc bx
    inc bx
    mov [bx], ax
    inc bx
    inc bx
    mov [bx], ax
    inc bx
    mov [bx], al
    inc bx
    mov [bx], al

    mov ax, 4c00h
    int 21
codesg ends
end