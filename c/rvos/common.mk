CROSS_COMPILE = riscv64-unknown-elf-
CFLAGS = -nostdlib -fno-builtin -march=rv32ima -mabi=ilp32 -g -Wall

QEMU = qemu-system-riscv32
QFLAGS = -nographic -smp 1 -machine virt -bios none

CC = ${CROSS_COMPILE}gcc
GDB = gdb-multiarch
# GDB = ${CROSS_COMPILE}
OBJDUMP = ${CROSS_COMPILE}objdump
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJREAD = ${CROSS_COMPILE}readelf