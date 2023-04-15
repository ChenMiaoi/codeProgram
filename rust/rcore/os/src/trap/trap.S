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
    mv      a0, sp
    call    trap_handler                        # 进入到trap的处理函数，位于trap::mod::trap_handler

__restore:                                      # __restore(cx_addr: usize)
    mv      sp, a0                              # 将cx_addr存入sp中

    ld      t0, 32*8(sp)                        # 陷入内核前的sstatus信息，载入t0
    ld      t1, 33*8(sp)                        # 陷入内核前的sepc信息，载入t1
    ld      t2, 2*8(sp)                          # 陷入内核前的用户栈指针, 载入t2

    csrw    sstatus, t0                         # 读取到当前的sstatus
    csrw    sepc, t1                            # 读取到当前的sepc
    csrw    sscratch, t2                        # 读取到当前的sscratch

    ld      ra, 1*8(sp)                         # 开始加载通用寄存器
    ld      gp, 3*8(sp)
    .set    n, 5
    .rept   27
            LOAD_GP %n
            .set n, n+1
    .endr

    addi    sp, sp, 34*8                        # 恢复栈
    csrrw   sp, sscratch, sp                    # 将sscratch的用户栈写入sp中，sp的内核栈指向sscratch
                                                # 也就是sp -> user_stack, sscratch -> kernel_stack
    sret                                        # sret会从sepc寄存器中获取返回地址，然后spec设置pc + 4，
                                                # 然后从sstatus中读取新的特权和状态为，设定为新值，从scause中读取异常，重置为0， 然后返回