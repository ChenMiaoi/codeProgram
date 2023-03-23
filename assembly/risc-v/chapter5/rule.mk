include ./common.mk

.DEFALT_GOAL := all
all:
	@ ${CC} ${CFLAGS} ${SRC} -Ttext=0x800000000 -o ${EXEC}.elf
	@ ${OBJCOPY} -O binary ${EXEC}.elf ${EXEC}.bin