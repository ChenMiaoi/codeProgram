; 用div计算data段中的第一个数据除以第二个数据后的结果，商存在第三个数据的存储单元中
assume cs:codesg, ds:data

; dd是double word的意思，也就是双字型数据

data segment
    dd 100001
    dw 100
    dw 0
data ends

codesg segment
start:
    mov ax, data
    mov ds, ax
    mov ax, ds:[0] ; 将低16位存储在ax中
    mov dx, ds:[2] ; 将高16位存储在dx中
    div word ptr ds:[4]
    mov ds:[6], ax ; 将商存储到对应内存单元中
codesg ends

end start