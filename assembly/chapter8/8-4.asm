; dup操作符
; dup由编译器识别处理的符号，用来做数据的重复

assume ds:data

data segment
    db 3 dup (0)
    ; 定义了三个字节，他们的值都是0，相当于 db 0, 0, 0
    db 3 dup (0, 1, 2)
    ; 定义了九个字节，相当于 db 0, 1, 2, 0, 1, 2, 0, 1, 2
    db 200 dup (0)
    ; 定义了两百个字节的栈段
data ends