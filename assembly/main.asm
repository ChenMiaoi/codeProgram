assume cs:codesg
; assume假定某一段寄存器和程序中的某一个用segment...ends定义的段相连

; segment...ends是一对成对使用的伪指令，且必须成对出现。 segment表示一个段的开始，ends表示一个段的结束
; 汇编程序由很多段组成
codesg segment
    mov ax, 0123h
    mov bx, 0456h
    add ax, bx
    add ax, ax

    mov ax, 4c00h
    int 21h
codesg ends

end
; end是一个汇编程序结束的标志