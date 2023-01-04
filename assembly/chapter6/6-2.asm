; 使用栈，将程序中的数据逆序存放
; 定义的数据放在CS：0～CS：F中

assume cs:code

code segment
    dw 0123h, 0456h, 0789h, 0abch, 0defh, 0fedh, 0cbah, 0987h ; 10h
    dw 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ; 20h
    ; 定义16个字型数据，用于栈的使用
    start:
        mov ax, cs
        mov ss, ax
        mov sp, 30h ; 栈底从程序第一条命令出开始，也就是30h

        mov bx, 0
        mov cx, 8
    s:
        push cs:[bx]
        add bx, 2
        loop s

        mov bx, 0
        mov cx, 8
    s0:
        pop cs:[bx]
        add bx, 2
        loop s0

        mov ax, 4c00h
        int 21h
code ends

end start