        AREA DecimalConversion, CODE, READONLY
        ENTRY

ToDec   ADR     r0, Convert             ; 指向要转换的数据
        LDR     a2, [r0]                ; 将要转换的数据加载到参数寄存器a2

        ADR     a1, String              ; 将缓冲区地址加载到参数寄存器a1
        BL      utoa                    ; 调用转换例程
        ADR     r1, String              ; 指向结果串
        MOV     r2, #10                 ; 打印结果(0xFFFFFFFF最多十个数字)

PrtLoop LDR     r0, [r1], #1            ; 获得一个字符并且指针递增
        SWI     0                       ; 打印字符
        SUBS    r2, r2, #1              ; 循环计数器递减
        BNE     PrtLoop                 ; 重复，直到10个数字均已打印
        SWI     17                      ; 退出(调用O/S功能0x11)

utoa    STMFD   sp!, { v1, v2, lr }     ; 将寄存器转换为十进制串，保存寄存器 
        MOV     v1, a1                  ; 保存参数a1， 因为div10会覆盖
        MOV     v2, a2                  ; 保存参数a2
        MOV     a1, a1                  ; div10要求参数在a1中
        BL      div10                   ; 调用div10计算a1 = a1 / 10
        SUB     v2, v2, a1, LSL #3      ; v2减去10倍的a1(a2 = a2 - 10a1)
        SUB     v2, v2, a1, LSL #1      ; 注意用8p + 2p = 10p

        CMP     a1, #0                  ; 商是否为0
        MOVNE   a2, a1                  ; 如果不为0，将其保存在a2
        MOV     a1, v1                  ; 将指针保存在a1
        BLNE    utoa                    ; 如果不为0，则递归调用
        ADD     v2, v2, #'0'            ; 通过加上0x30将最后的数字转换为ASCII
        STRB    v2, [a1], #1            ; 将该数字保存在缓冲区最后
        LDMFD   sp!, { v1, v2, pc }     ; 恢复寄存器并从递归函数返回

div10   SUB     a2, a1,     #10         ; a1除以10的子程序
        SUB     a1, a1, a1, LSR #2      ; 商在a1中，余数在a2中，返回
        ADD     a1, a1, a1, LSR #4      ; 除法！乘以1 / 10 = 0.1
        ADD     a1, a1, a1, LSR #8
        ADD     a1, a1, a1, LSR #16
        MOV     a1, a1,     LSR #3
        ADD     a3, a1, a1, ASL #2
        SUBS    a2, a2, a3, ASL #1
        ADDPL   a1, a1,     #1
        ADDMI   a2, a2,     #10
        MOV     pc, lr                  ; 商在a1中，返回

Convert DCD     #0x12345678             ; 数据

String  DCD     0x0                     ; 结果的位置
        END