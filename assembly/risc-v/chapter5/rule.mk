include ../common.mk

# 默认的编译目标
# -Ttext
# 设置程序的初始化运行地址，riscv架构下，一般以0x8000 0000作为_start的地址
# objcopy使得elf中的其他数据被剥离，只剩下机器指令
.DEFALT_GOAL := all
all:
	@ ${CC} ${CFLAGS} ${SRC} -Ttext=0x80000000 -o ${EXEC}.elf
	@ ${OBJCOPY} -O binary ${EXEC}.elf ${EXEC}.bin

# 启动elf文件
# -kernel bzImage use 'bzImage' as kernel image
.PHONY: run
run: all
	@echo "Press Ctrl-A and then X tp exit"
	@echo "-------------------------------"
	@ ${QEMU} ${QFLAGS} -kernel ./${EXEC}.elf

# the use gdb to debug with qemu-system-riscv32
# -s shorthand for -gdb tcp::1234 默认使用1234端口
# -S freeze CPU at startup (use 'c' to start execution)
# 阻塞启动，在此处用于等待gdb的连接
.PHONY: debug
debug: all
	@echo "Press Ctrl-C and then input 'quit' to exit"
	@echo "------------------------------------------"
	@ ${QEMU} ${QFLAGS} -kernel ${EXEC}.elf -s -S &
	@ ${GDB} ${EXEC}.elf -q -x ${GDBINIT}

# 反汇编生成的elf文件
.PHONY: code
code: all
	@ ${OBJDUMP} -S ${EXEC}.elf | less

# 查看剥离后的bin文件中的机器指令数据
.PHONY: hex
hex: all
	@ hexdump -C ${EXEC}.bin

.PHONY: clean
clean:
	rm -rf *.o *.bin *.elf
