; div指令：
;   div reg
;   div 内存单元
; 1. 除数有8位和16位两种，且被除数是其的两倍
; 2. 被除数默认放在AX或AX和DX中，如果除数是8位，那么商和余数分别放在AL和AH中
;    如果除数是16位，则AX放商，DX放余数
; 3. 如果被除数是32位，则AX中放低16位，DX中放高16位

assume cs:codesg

; 现在对10001 / 100 进行编程
; 我们发现，10001 > 65535，也就是说，被除数是32位的，因此使用AX存放低16位，DX存放高16位 10001(d) -> 186A1(H)

; 对1001 / 100 进行编程

codesg segment
    mov dx, 1
    mov ax, 86A1h
    mov bx, 100
    div bx

    mov ax, 1001
    mov bl, 100 ; 此处用bl表示用8位除法
    div bl 

    mov ax, 1001
    mov byte ptr bx, 100
    div byte ptr bx
codesg ends

end