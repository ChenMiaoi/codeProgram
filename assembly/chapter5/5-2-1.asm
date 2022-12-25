; 编程，用加法计算123*236，结果保存在ax中
; assume codesg

; codesg segment
;     mov ax, 123
;     mov cx, 235

; loops:
;     add ax, ax
;     loop loops

;     mov ax, 4c00h
;     int 21h
; codesg ends

; end

; 提高效率
assume codesg

codesg segment
    mov ax, 235
    mov cx, 122

loops:
    add ax, ax
    loop loops

    mov ax, 4c00h
    int 21h
codesg ends

end