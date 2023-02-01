; jmp为无条件转移指令，可以只修改IP，也可以同时修改CS和IP
; jmp指令要给出两种信息
    ; 1. 转移的目的地址
    ; 2. 转移的距离(段间距离、段内短距离、段内近距离)

; jmp short 标号, 这种格式的jmp指令实现的是段内短转移，对IP的修改范围是-127～128,也就是向前最多128,向后最多127字节
assume cs:codesg

codesg segment
start:
    mov ax, 0
    jmp short s
    add ax, 1
s:
    inc ax

    mov ax, 4c00h
    int 21h
codesg ends

end start

; 经过调试后发现，CPU在执行jmp指令的时候不需要转移的目的地址，而是告诉了其要位移的距离
; 也就是说，jmp转变为机器码，就只有指令 + 位移距离
; 因此，实际上jmp short 标号的功能为：IP = IP + 8位位移
    ; 1. 8位位移 = 标号处的地址 - jmp指令后的第一个字节的地址
    ; 2. short表示此处的位移是8位，范围为-127～128
    ; 3. 8位位移由编译程序在编译时算出

; jmp near ptr 标号的功能为：IP = IP + 16位位移
    ; 表示段内近位移，是16位位移，范围为-32768～32767