TARGET 		:= riscv64gc-unknown-none-elf
MODE		:= release
APP_DIR		:= src/bin
BUILD_DIR	:= build
TARGET_DIR	:= target/${TARGET}/${MODE}

OBJDUMP		:= rust-objdump --arch-name=riscv64
OBJCOPY		:= rust-objcopy --binary-architecture=riscv64

PY			:= python3

APPS		:= $(wildcard $(APP_DIR)/*.rs)	# wildcard是Makefile的函数，其用途是列出具有特定扩展名的源文件，在此处是列出所有rs文件
ELFS		:= $(patsubst $(APP_DIR)/%.rs, $(TARGET_DIR)/%, $(APPS)) # patsubst用于模式替换，此处是将APP_DIR中的rs文件全部以APPS文件名替换到TARGET_DIR下，且除去文件后缀

binary:
	@echo $(ELFS)
	@python3 build.py
	@$(foreach elf, $(ELFS), \
		$(OBJCOPY) $(elf) --strip-all -O binary $(patsubst $(TARGET_DIR)/%, $(TARGET_DIR)/%.bin, $(elf)); \
		cp $(elf) $(patsubst $(TARGET_DIR)/%, $(TARGET_DIR)/%.elf, $(elf));)

make_pre:
	@mkdir -p $(BUILD_DIR)/bin/							# 创建build/bin/
	@mkdir -p $(BUILD_DIR)/elf/							# 创建build/elf/
	@mkdir -p $(BUILD_DIR)/app/							# 创建build/app/
	@mkdir -p $(BUILD_DIR)/asm/							# 创建build/asm
	@$(foreach t, $(APPS), cp $(t) $(BUILD_DIR)/app/;)	# 将需要编译的源文件全部复制到build/app下

build: clean make_pre binary
	@$(foreach t, $(ELFS), cp $(t).bin $(BUILD_DIR)/bin/;)
	@$(foreach t, $(ELFS), cp $(t).elf $(BUILD_DIR)/elf/;)

clean:
	@cargo clean
	@rm -rf $(BUILD_DIR)

all: build

.PYTHON: build make_pre build clean