; jcxz指令为有条件转移指令，所有的有条件转移指令都是短转移
; jcxz 标号
; 其实际意义为：if (cx == 0) jmp short 标号

; 补全程序，利用jcxz指令，实现在内存中2000H段中查找第一个值为0的字节，找到后
; 将它的偏移地址存储在cx中

assume cs:codesg

codesg segment
start:
    mov ax, 2000h
    mov ds, ax
    mov bx, 0
s:
    ; *** YOUR CODE ***
    mov cl, [bx]
    mov ch, 0
    jcxz ok
    inc bx
    ; *** END *** 
    jmp short s
ok:
    mov dx, bx
    
    mov ax, 4c00h
    int 21h
codesg ends

end start