.altmacro
.macro SAVE_SN n
    sd      s\n, (\n + 2) * 8(a0)
.endm
.macro LOAD_SN n
    ld      s\n, (\n + 2) * 8(a1)
.endm

    .section .text
    .global __switch
    # __switch(
    #     current_task_cx_ptr: *mut TaskContext,
    #     next_task_cx_ptr: *const TaskContext
    # )
__switch:
    sd      sp, 8(a0)                               # 保存当前寄存器的内核栈指针
    sd      ra, 0(a0)                               # 保存当前任务的返回地址
    .set    n, 0                                    # 保存s0~s11寄存器信息
    .rept   12
        SAVE_SN %n
        .set    n , n + 1
    .endr

    ld      ra, 0(a1)                               # 加载下一个任务的返回地址
    .set    n, 0                                    # 加载下一个任务的寄存器信息
    .rept   12
        LOAD_SN %n
        .set    n, n + 1
    .endr

    ld      sp, 8(a1)                               # 加载下一个任务的内核栈指针
    ret