include ./common.mk

SRCS_ASM = \
	start.S	\
	
SRCS_C	 = \
	kernel.c \

# .S -> .o
OBJS  = ${SRCS_ASM: .S=.o}
# .c -> .o
OBJS += ${SRCS_C:   .c=.o}

.DEFAULT_GOAL := all
all: os.elf

# .o -> .elf
os.elf: ${OBJS}
	${CC} ${CFLAGS} -Ttext=0x80000000 -o os.elf $^
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
	@${GDB} os.elf -q -x ./gdbinit

.PHONY : code
code: all
	@${OBJDUMP} -S os.elf | less

.PHONY : clean
clean:
	rm -rf *.o *.bin *.elf
