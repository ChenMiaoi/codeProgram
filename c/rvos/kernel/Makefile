SRCS_ASM = 		\
	start.S		\
	mem.S		\
	switch.S	\
	# ../usys.S	\
	
SRCS_C	 = 		\
	kernel.c 	\
	uart.c		\
	printf.c	\
	mm.c		\
	sched.c		\
	user.c		\
	trap.c		\
	plic.c		\
	timer.c		\
	lock.c		\
	# syscall.c	\

# .S -> .o
OBJS  = ${SRCS_ASM: .S=.o}
# .c -> .o
OBJS += ${SRCS_C:   .c=.o}

.DEFAULT_GOAL := all
all: os.elf

# .o -> .elf
os.elf: ${OBJS}
	${CC} ${CFLAGS} -T os.ld -o os.elf $^
	${OBJCOPY} -O binary os.elf os.bin

# .c -> .o
%.o : %.c
	${CC} ${CFLAGS} -c -o $@ $^
# .S -> .o
%.o : %.S
	${CC} ${CFLAGS} -c -o $@ $^

run: all
	@${QEMU} -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo "------------------------------------"
	@${QEMU} ${QFLAGS} -kernel os.elf

.PHONY : debug
debug: all
	@echo "Press Ctrl-C and then input 'quit' to exit GDB and QEMU"
	@echo "-------------------------------------------------------"
	@${QEMU} ${QFLAGS} -kernel os.elf -s -S &
	@${GDB} os.elf -q -x ../gdbinit

.PHONY : dash-debug
dash-debug: all
	@echo "Press Ctrl-C and then input 'quit' to exit GDB and QEMU"
	@echo "-------------------------------------------------------"
	@${QEMU} ${QFLAGS} -kernel os.elf -s -S &
	@${GDB} os.elf -q

.PHONY : code
code: all
	@${OBJDUMP} -S os.elf | less

.PHONY : dump
dump: all
	@${OBJREAD} -S os.elf | less

.PHONY : clean
clean:
	rm -rf *.o *.bin *.elf