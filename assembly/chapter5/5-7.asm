assume cs:code

code segment
    mov ax, 0
    mov ds, ax
    mov ds:[26h], ax ; 在0000:0026内，存放着重要数据，运行到这一步会发生死机

    mov ax, 4c00h
    int 21h
code ends

end