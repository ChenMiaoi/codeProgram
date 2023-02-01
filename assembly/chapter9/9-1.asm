; 可以修改IP，或同时修改CS和IP的指令统称为转移指令
; 操作符offset在汇编语言中是由编译器处理的符号，其功能是取得标号的偏移地址

; assume cs:codesg

; codesg segment
; start:
;     mov ax, offset start ; 相当于 mov ax, 0
; s:
;     mov ax, offset s ; 相当于 mov ax, 3。因为第一条指令的长度为3,s的偏移地址是3
; codesg ends

; end start

; 添加两条指令，使得该程序在运行中将s处的一条指令复制到s0处
assume cs:codesg

codesg segment
s:
    mov ax, bx ; mov ax, bx的机器码占两个字节
    mov si, offset s
    mov di, offset s0
    mov ax, cs:[si]
    mov cs:[di], ax
s0:
    nop ; nop的机器码占一个字节
    nop

    mov ax, 4c00h
    int 21h
codesg ends

end s