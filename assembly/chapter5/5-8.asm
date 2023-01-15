; 将内存ffff：0～ffff：b单元中的数据复制到0：200～0：20b单元中

assume cs:code 

code segment
    mov bx, 0
    mov cx, 12
s:
    mov ax, 0ffffh
    mov ds, ax
    mov dl, [bx] ; 因为[bx]是8字节，因此用dl，将ffff：bx中的数据送入dl

    mov ax, 0020h
    mov ds, ax
    mov [bx], dl ; 将dl(ffff：bx)中的数据送入0020：bx中

    inc bx
    loop s

    mov ax, 4c00h
    int 21h
code ends

end