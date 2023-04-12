TARGET 		:= riscv64gc-unknown-none-elf
MODE 		:= debug
KERNEL_ELF 	:= target/${TARGET}/${MODE}/os
KERNEL_BIN 	:= ${KERNEL_ELF}.bin

ifeq (${MODE}, release)
	MODE_ARG := --release
endif

BOOTLOADER 	:= ../bootloader/rustsbi-qemu.bin

KERNEL_ENTRY_PA := 0x80200000

OBJDUMP := rust-objdump --arch-name=riscv64
OBJCOPY := rust-objcopy --binary-architecture=riscv64

build: env ${KERNEL_BIN}

env:
	(rustup target list | grep "riscv64gc-unknown-none-elf (installed)") || rustup target add $(TARGET)
	cargo install cargo-binutils
	rustup component add rust-src
	rustup component add llvm-tools-preview

${KERNEL_BIN}: kernel
	@${OBJCOPY} ${KERNEL_ELF} --strip-all -O binary $@

kernel:
	@make -C ../user build
	@cargo build ${MODE_ARG}

run: run-inner

run-inner: build
	@qemu-system-riscv64	\
		-machine virt 		\
		-nographic			\
		-bios ${BOOTLOADER}	\
		-device loader,file=${KERNEL_BIN},addr=${KERNEL_ENTRY_PA}

debug-server: build
	@qemu-system-riscv64 -machine virt -nographic -bios $(BOOTLOADER) -device loader,file=$(KERNEL_BIN),addr=$(KERNEL_ENTRY_PA) -s -S

debug-client:
	@riscv64-unknown-elf-gdb -ex 'file $(KERNEL_ELF)' -ex 'set arch riscv:rv64' -ex 'target remote localhost:1234'

clean:
	@cargo clean

.PHONY: build env kernel clean run-inner debug-client debug-server