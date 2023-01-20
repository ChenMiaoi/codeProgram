assume cs:codesg, ds:datasg

datasg segment
    db 'BaSiC'
    db 'iNfOrMaTiOn'
datasg ends

codesg segment
start:
    mov ax, datasg
    mov ds, ax

    mov bx, 0
    mov cx, 5

    ; 由于目前我们没有学习判断的指令，因此我们需要找到另一种方式去实现判断
    ; 而通过观察得出，大写字母的ASCII码对应的二进制在第6位处总是0
    ; 而小写字母的ASCII码对应的二进制在第6位总是1
    ; 因此，我们可以使用and、or指令来使某一特定位置变化

s0:
    mov al, [bx]    ; 取出想要变化的字母
    add al, 11011111B   ; 进行与操作，大写
    mov [bx], al    ; 将变化后的字母返回到原内存地址处
    inc bx
    loop s0

    mov bx, 5
    mov cx, 11

s1:
    mov al, [bx]
    or  al, 00100000B   ; 进行或操作，小写
    mov [bx], al
    inc bx
    loop s1

    mov ax, 4c00h
    int 21h
codesg ends

end start