; loop指令为循环指令，所有的循环指令都是短转移，在对应的机器码中包含转移的位移
; loop 标号
; 其实际意义为：if (cx-- != 0) jmp short 标号

; 补全程序，利用jcxz指令，实现在内存中2000H段中查找第一个值为0的字节，找到后
; 将它的偏移地址存储在cx中

assume cs:codesg

codesg segment
start:
    mov ax, 2000h
    mov ds, ax
    mov bx, 0

s:
    mov cl, [bx]
    mov ch, 0
    ; *** YOUR CODE ***
    inc cx ; 因为 loop 是 cx - 1 = 0才会退出循环，如果已经为0了，那么0 - 1 != 0了
    ; *** END ***
    inc bx
    loop s

ok:
    dec bx ; dec指令和inc相反，dec bx ==> bx = bx - 1
    mov dx, bx

    mov ax, 4c00h
    int 21h
codesg ends

end start