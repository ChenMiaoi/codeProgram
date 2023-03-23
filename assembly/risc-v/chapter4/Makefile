GCC=riscv64-unknown-elf-gcc
ARCH=-march=rv32im
ABI=-mabi=ilp32
QEMU=qemu-riscv32
DEBUG=-g

hello:hello.o
	$(GCC) $(ARCH) $(ABI) $^ -o $@
hello.o:hello.c
	$(GCC) $(ARCH) $(ABI) $^ -c $@

.PHONY:run
run:
	$(QEMU) ./hello

.PHONY:debug
debug:
	$(GCC) $(ARCH) $(ABI) hello.c -c hello.o $(DEBUG)
	$(GCC) $(ARCH) $(ABI) hello.o -o hello $(DEBUG)

.PHONY:clean
clean:
	rm -rf hello hello.o