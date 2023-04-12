TARGET 		:= riscv64gc-unknown-none-elf
MODE		:= release
APP_DIR		:= src/bin
BUILD_DIR	:= build
TARGET_DIR	:= target/${TARGET}/${MODE}

OBJDUMP		:= rust-objdump --arch-name=riscv64
OBJCOPY		:= rust-objcopy --binary-architecture=riscv64

PY			:= python3

APPS		:= $(wildcard $(APP_DIR)/*.rs)
ELFS		:= $(patsubst $(APP_DIR)/%.rs, $(TARGET_DIR)/%, $(APPS))

binary:
	@echo $(ELFS)
	@python3 build.py
	@$(foreach elf, $(ELFS), \
		$(OBJCOPY) $(elf) -- strip-all -O binary $(patsubst $(TARGET_DIR)/%, $(TARGET_DIR)/%.bin, $(elf)) \
		cp $(elf) $(patsubst $(TARGET_DIR)/%, $(TARGET_DIR)/%.elf, $(elf));)

make_pre:
	@mkdir -p $(BUILD_DIR)/bin/
	@mkdir -p $(BUILD_DIR)/elf/
	@mkdir -p $(BUILD_DIR)/app/
	@mkdir -p $(BUILD_DIR)/asm/
	@$(foreach t, $(APPS), cp $(t) $(BUILD_DIR)/app/;)

build: clean make_pre binary
	@$(foreach t, $(ELFS), cp $(t).bin $(BUILD_DIR)/bin/;)
	@$(foreach t, $(ELFS), cp $(t).elf $(BUILD_DIR)/elf/;)

clean:
	@cargo clean
	@rm -rf $(BUILD_DIR)

all: build

.PYTHON: build make_pre build clean