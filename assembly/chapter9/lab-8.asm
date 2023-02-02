; 分析下面的程序，在运行前思考，这个程序能否正确返回？
; 运行后思考，为什么是这样的结果

; 应该是能正常返回的
; 运行后，结果是正常返回，在反汇编中，我们发现，在标签s2: jmp short s1中，其机器码为EBF6
; 而EB代表jmp， F6表示了跳转位移，转为十进制就是-10，且，当前的CS：IP=04B0：0020
; 那么转跳位移为-10,则CS：IP=04B0：0010，此时对应的汇编为CS，也就是说
; 其实jmp short s1真正转跳到了CS：0000也就是codesg segment语句，执行mov ax, 4c00h, int 21h
; 因此能够正常执行
; *** 这其实反映了，jmp实际上是计算标号的位移来进行跳转，而非是标号的目的地址进行跳转，因此我们使用时，也应该注意计算jmp与标号之间的位移距离 ***

assume cs:codesg

codesg segment
    mov ax, 4c00h
    int 21h
start:
    mov ax, 0
s:
    nop
    nop ; 这两条被替换为 jmp short s1

    mov di, offset s
    mov si, offset s2
    mov ax, cs:[si]
    mov cs:[di], ax
s0:
    jmp short s
s1:
    mov ax, 0
    int 21h
    mov ax, 0
s2:
    jmp short s1
    nop
codesg ends

end start