.altmacro
.macro SAVE_GP n                                # 保存寄存器的宏
    sd x\n, \n*8(sp)
.endm

.macro LOAD_GP n
    ld x\n, \n*8(sp)
.endm

    .section .text
    .global __alltraps
    .global __restore
    .align 2

__alltraps:
    csrrw   sp, sscratch, sp                    # 特权指令，使得sp指向内核栈，scratch指向用户栈
    addi    sp, sp, -34*8                       # 为内核栈开辟空间
                                                # 以下是上下文的保存
    sd      ra, 1*8(sp)                         # 存入ra返回地址
                                                # 跳过了x2(sp)，在之后会存入
    sd      gp, 3*8(sp)
    .set    n, 5                                # 使用宏，循环存入x5~x31
    .rept   27
            SAVE_GP %n
            .set    n, n+1
    .endr

    csrr    t0, sstatus                         # 将目前特权信息读入到t0，对应了TrapContext::sstatus
    csrr    t1, sepc                            # 将陷入内核时的地址读取给t1，对应了TrapContext::sepc
    sd      t0, 32*8(sp)                        # 存入栈中
    sd      t1, 33*8(sp)

    csrr    t2, sscratch                        # 读取用户栈指针到t2
    sd      t2, 2*8(sp)                         # 存入栈中
    mov     a0, sp
    call    trap_handler                        # 进入到trap的处理函数，位于trap::mod::trap_handler