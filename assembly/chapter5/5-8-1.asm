; 将内存ffff：0～ffff：b单元中的数据复制到0：200～0：20b单元中

; 因为ffff：X和0020：X相距大于64KB，在不同的64KB段中，设置两次DS是正确的，但是这样效率不高
; 因此可以用两个段寄存器来实现

assume code 

code segment
    mov ax, 0ffffh
    mov ds, ax

    mov ax, 0020h
    mov es, ax

    mov bx, 0
    mov cx, 12
s:
    mov dl, [bx]
    mov es:[bx], dl
    inc bx
    loop s

    mov ax, 4c00h
    int 21h
code ends

end