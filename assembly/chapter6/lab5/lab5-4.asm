; 编写code段代码，将a段和b段中的内容依次相加，将结果保存在c段中

assume cs:code

a segment
    db 1, 2, 3, 4, 5, 6, 7, 8
a ends

b segment
    db 1, 2, 3, 4, 5, 6, 7, 8
b ends

c segment
    db 0, 0, 0, 0, 0, 0, 0, 0
c ends

code segment
start:
    mov ax, a
    mov ds, ax ; 将A段数据送入ds段寄存器中
    mov ax, b
    mov es, ax ; 将B段数据送入es段寄存器中

    mov cx, 8
    mov bx, 0
s:
    mov dx, [bx]
    add dx, es:[bx] ; 将A、B段对应数据相加后存入DX中
    push ds ; 保存ds寄存器，因为我们的段寄存器使用完了，必须空出一个寄存器来接受C段数据
    mov ax, c
    mov ds, ax ; 将C段数据送入ds段寄存器中
    mov [bx], dl ; 将相加的结果送入C段中
    pop dx ; 重新返回ds寄存器，也就是A段的数据内容

    inc bx
    loop s

    mov ax, 4c00h
    int 21h
code ends

end start