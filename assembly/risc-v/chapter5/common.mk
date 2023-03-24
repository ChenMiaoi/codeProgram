CROSS_COMPILE = riscv64-unknown-elf-
# CFLAGS is the options of CROSS_COMPILE
# nostdlib - 不连接系统标准启动文件和标准库文件，只把指定的文件传递给链接器
# 因为C语言执行的第一条指令并不是main函数，而是一些标准库的启动文件，这些文件设置了C程序的堆栈，然后调用main
# 而裸机开发时，并不需要这些，我们会自行指定
# fno-builtin
# 不适用内建函数(内建函数是指编译器提供的函数)，裸机开发一般会自行重写函数，就不需要编译器来提供，而且也防止重名
CFLAGS = -nostdlib -fno-builtin -march=rv32im -mabi=ilp32 -g -Wall

QEMU = qemu-system-riscv32
# QFLAGS is the options of QEMU
# nographic - disable graphical output and redirect serial I/Os to console
# 因为我们是想要通过qemu模拟器来进行调试，因此不需要GUI
# smp - set the number of initial CPUs to 'n' [default=1]
# 因为只需要进行debug，所以一颗cpu就够了
# machine - selects emulated machine
# bios - set the filename for the BIOS
# 因为只是调试，而非真正的启动内核，所以设置为none
QFLAGS = -nographic -smp 1 -machine virt -bios none

CC = ${CROSS_COMPILE}gcc
GDB = ${CROSS_COMPILE}gdb
OBJCOPY = ${CROSS_COMPILE}objcopy
OBJDUMP = ${CROSS_COMPILE}objdump

EXEC = test
SRC = ${EXEC}.s
GDBINIT = ../gdbinit