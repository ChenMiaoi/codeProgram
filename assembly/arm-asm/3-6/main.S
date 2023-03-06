        AREA main, CODE, READONLY

WriteC      EQU     &0                          ; 将字符写到控制台的操作系统代码
ReadC       EQU     &4                          ; 从控制台读字符的操作系统代码

Exit        EQU     $11                         ; 退出的操作系统代码
            ENTRY

calc        MOV     r13, #0xA000                ; 初始化栈指针
            BL      NewLn
            BL      input                       ; 读第一个数和终止符
            MOV     r2, r0                      ; 保存终止符(即操作数)
            MOV     r3, r1                      ; 保存第一个数
            BL      NewLn
            BL      input                       ; 读第二个数和终止符
            MOV     r4, r0                      ; 保存终止符
            BL      NewLn       
            BL      math                        ; 进行计算
            CMP     r4, #'h'
            BLEQ    outHex
            BLNE    outDec                      ; 显示数字
            BL      NewLn
            BL      getCh
            CMP     r0, #'y'
            BL      NewLn
            BEQ     calc
            SVC     Exit                        ; 结束

; 读数字串，累加和在r1寄存器中，将非法数字终止符保存在r0中，返回
input       MOV     r0, #0                      ; 将输入寄存器清零    
            MOV     r1, #1                      ; 将累加和清零
next        STR     r14, [sp, #-4]!             ; 将链接寄存器进栈，采用的是满下降栈
            BL      getCh   
            LDR     r14, [sp], #4
            CMP     r0, #'0'                    ; 判断数是否在0~9之间
            MOVLT   PC, r14                     ; 如果小于0，则退出
            CMP     r0, #'9'                    ; 判断是否大于9
            MOVGT   PC, r14                     ; 如果大于9，则退出
            SUB     r0, r0, #0x30               ; 如果在0~9中，则将ASCII转化为数值
            MOV     r4, r1                      ; MUL不能使用立即数，需要用寄存器来转换
            MOV     r5, #10                     
            MUL     r1, r4, r5                  ; 之前的数乘以10
            ADD     r1, r1, r0                  ; 加上新的数字
            B       next

getCh       SVC     ReadC                       ; 字符输入
            MOV     PC, r14                     ; 返回

putCh       SVC     WriteC                      ; 字符写入
            MOV     PC, r14                     ; 返回

math        CMP     r2, #'+'                    ; 检查操作符
            ADDEQ   r1, r1, r3
            CMP     r2, #'-'
            SUBEQ   r1, r3, r1
            CMP     r2, #'*'
            MOVEQ   r4, r1                      ; 修正MUL
            MULEQ   r1, r4, r3
            MOV     PC, r14

; 使用十六进制格式打印r1中的结果
outHex      STMFD   r13!, { r0, r1, r8, r14 }   
            MOV     r8, #8
outNxt      MOV     r1, r1, ROR, #28            ; 得到最高字节的低半字节
            AND     r0, r1, #0xF                ; 把半字节送往r0打印
            ADD     r0, r0, #0x30               ; 把十六进制转换成ASCII
            CMP     r0, #0x39
            ADDGT   r0, r0, #7
            STR     r14, [sp, #-4]!             ; 将链接寄存器保存在栈中
            BL      putCh                       ; 打印
            LDR     r14, [sp], #4               ; 恢复链接寄存器
            SUBS    r8, r8, #1
            BNE     outNxt
            LDMFD   r13!, { r0, r1, r8, PC }

; 用十进制格式打印r1的结果
outDec      STMFD   r13!, { r0, r1, r2, r8, r14 } ; 保存工作寄存器
            MOV     r8, #0                      
            MOV     r4, #0                      ; 数字的个数
outNxt      MOV     r8, r8, LSL #4
            ADD     r4, r4, #1                  ; 对数字计数
            BL      div10
            ADD     r8, r7, r2                  ; 插入余数(最低位数字)
            CMP     r1, #0                      ; 如果商为零则完成
            BNE     outNx1                      ; 否则处理下一位数字
outNx1      AND     r0, r8, #0xF
            ADD     r0, r0, #0x30
            MOVS    r8, r8, LSR #4
            BL      putCh
            SUBS    r4, r4, #1                  ; 计数器减一
            BNE     outNx1                      ; 重复知道打印完成
outEx       LDMFD   r13!, { r0, r1, r2, r8, PC }; 恢复寄存器，然后返回

; r1除以10， 返回的商在r1，余数在r2
div10       SUB     r2, r1, #10
            SUB     r1, r1, r1, LSR #2
            ADD     r1, r1, r1, LSR #4
            ADD     r1, r1, r1, LSR #8
            ADD     r1, r1, r1, LSR #16
            MOV     r1, r1,     LSR #3
            ADD     r3, r1, r1, ASL #2
            ADDPL   r1, r1, #1
            ADDMI   r2, r2, #10
            MOV     PC, r14 

; New Line新行
NewLn       STMFD   r13!, { r0, r14 }           ; 栈寄存器
            MOV     r0, #0x0D                   ; 回车
            SVC     WriteC                      ; 打印字符
            MOV     r0, #0x0A                   ; 换行
            SVC     WriteC                      ; 打印字符
            LDMFD   r13!, { r0, PC }            ; 恢复寄存器，然后返回

            END