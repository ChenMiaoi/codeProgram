assume cs:codesg

data segment
    db '1975', '1976', '1977', '1978', '1979', '1980', '1981', '1982', '1983'
    db '1984', '1985', '1986', '1987', '1988', '1989', '1990', '1991', '1992'
    db '1993', '1994', '1995' ; 以上是表示21年的21个字符串 -> 21 * 4 = 54H -> data:[0] 每次+4

    dd 16, 22, 382, 1356, 2390, 8000, 16000, 24486, 50065, 97479, 140417, 197514
    dd 345980, 590827, 803530, 1183000, 1843000, 2759000, 3753000, 4649000, 5937000
    ; 以上是对应每年的总收入 -> 21 * 8 = 108H -> data:[54] 每次 + 8

    dw 3, 7, 9, 13, 28, 38, 130, 220, 476, 778, 1001, 1442, 2258, 2793
    dw 4037, 5635, 8226, 11542, 14430, 15257, 17800 ; 以上是表示每年的员工数 -> 21 * 2 = 2AH -> data:[A8] -> 每次 + 2
data ends

table segment
    db 21 dup ('year summ ne ?? ') ; table:[0] -> 每次 + 16
table ends

; 编程，将data段的数据按如下格式写入到table段中，并计算21年内人均收入

; 年份(4字节)_收入(4字节)_雇员数(2字节)_人均收入(2字节)_

stack segment
    db 8 dup (0)
stack ends

; 编写的暂时有BUG，没有处理好最后对于雇员数的写入，其余没有问题

codesg segment
start:
    mov ax, data
    mov ds, ax
    mov ax, table
    mov es, ax
    mov ax, stack
    mov ss, ax
    mov sp, 10h

    mov bx, 0
    mov di, 0
    mov si, 0
    mov bp, 0
    mov cx, 21
s0:
    push cx
    mov si, 0
    mov cx, 4
    s1:
        mov al, ds:[bx].0h[si]
        mov es:[bp].0h[si], al
        inc si
        loop s1
    mov si, 0
    mov cx, 4
    s2:
        mov al, ds:[bx].54h[si]
        mov es:[bp].5h[si], al
        inc si
        loop s2
    mov si, 0
    mov cx, 2
    s3: 
        mov al, ds:[bx].0a8h[si]
        mov es:[bp].0ah[si], al
        inc si
        loop s3
    mov si, 0
    mov cx, 2
    
    mov ax, ds:[di].54h[0]
    mov dx, ds:[di].54h[2]
    div word ptr ds:[bx].0a8h
    mov word ptr es:[bp].13h, ax

    pop cx
    add bp, 16
    add di, 4
    add bx, 4
    loop s0

    mov ax, 4c00h
    int 21h
codesg ends

end start