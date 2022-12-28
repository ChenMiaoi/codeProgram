assume cs:codesg

codesg segment
    mov ax, 2000h
    mov ds, ax
    mov al, [0]
    mov bl, [1]
    mov cl, [2]
    mov dl, [3]

    mov ax, 4c00h
    int 21h
codesg ends

end

; 在源代码中，[idata]会被解释为一个内存单元，而不会将其解释为内存单元的偏移地址
; 但是对于[BX]来说，在源代码中使用还是被看作为DS：[BX]
; 如果想要在源代码中直接被解释为偏移地址，那么需要显式声明，例如：DS：[0]