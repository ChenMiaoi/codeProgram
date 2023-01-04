; 编程计算以下八个数据的和，结果存放在寄存器AX中
; 0123h, 0456h, 0789h, 0defh, 0fedh, 0cbah, 0987h

; 我们不能随便决定哪一块空间是有效的，因此我们提前定义好我们需要处理的数据
; 然后经过编译连接后，这部分数据被操作系统分配了一块可以使用的合法空间

assume cs:code

code segment
    dw 0123h, 0456h, 0789h, 0abch, 0defh, 0fedh, 0cbah, 0987h
    start:
        mov bx, 0
        mov ax, 0
        mov cx, 8
    s:
        add ax, cs:[bx]
        add bx, 2
        loop s

        mov ax, 4c00h
        int 21h
code ends

end start

; 第一行中，dw的意义是“define word”也就是定义字型数据
; 此处定义了八个字型，也就是占据了16个字节

; 用dw定义的字型数据处于代码段的最开始，所以其偏移地址是
; 那么对应的数据偏移地址为：0, 2, 4, 6, 8, A，C，E
; 所以在程序中的地址就是CS:SA(对应的偏移地址)

; 但是，由于我们现在程序的入口处不是我们执行的语句，直接执行是会出错的
; 因此，我们需要定义一个start标签