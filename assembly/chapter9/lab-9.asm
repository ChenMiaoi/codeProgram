; 编程，在屏幕中间分别显示绿色、绿底红色、白底蓝色的字符串'welcome to masm!'

assume cs:codesg, es: datasg, ss: stack

datasg segment
    db 'welcome to masm!'
    db 02h, 24h, 71h
    ; 对应的属性为：绿色、绿底红色、白底蓝色
datasg ends

stack segment
    db 8 dup (0)
stack ends

codesg segment
start:
    mov ax, 0B800h          ; 第0页的段地址
    mov ds, ax
    mov ax, datasg
    mov es, ax              ; 数据段
    mov ax, stack
    mov ss, ax
    mov sp, 10h

    mov si, 0
    mov di, 0
    mov bx, 7bch            ; 第12行中间的偏移地址开始 A0 * 12(d) + BC -> BC是第40列开始的位置
                            ; 因为屏幕一共160字节，数据有32字节，那么从60字节开始就是在中间
    mov cx, 3               ; 属性的遍历

s0:
    push cx
    mov cx, 16
    s1:
        mov al, es:[di]
        mov [bx], al        ; 数据的写入
        mov ah, es:[si].10h
        or  ah, 0F0h        ; 加入闪烁效果
        mov [bx].1h, ah     ; 属性的写入
        inc di
        add bx, 2           ; 属性 + 数据占据两个字节
        loop s1
    add bx, 80h             ; 每一行是80个字，一共160字节，换到下一行去, 但是由于现在bx已经增加了16 * 2了，所以需要减去32
    inc si                  ; 换数据的属性
    mov di, 0               ; 重置到数据的开头
    pop cx                  ; 恢复cx
    loop s0

    mov ax, 4c00h
    int 21h
codesg ends

end start