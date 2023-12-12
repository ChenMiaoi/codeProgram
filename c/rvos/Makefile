include ./common.mk

export CROSS_COMPILE CFLAGS QEMU QFLAGS \
	CC GDB OBJDUMP OBJCOPY OBJREAD

ifdef TEST_TRAP
	CFLAGS += -DTRAP_TEST
endif

ifdef TEST_IER
	CFLAGS += -DEX_IER_TEST
endif

.PHONY: all run debug dash-debug code dump clean 

SUB := kernel

all: subdirs
	@echo "Building the os"

subdirs:
	for dir in $(SUB); do \
		$(MAKE) -C $$dir;\
	done

run: all
	$(MAKE) -C kernel run

debug: all
	$(MAKE) -C kernel debug

dash-debug: all
	$(MAKE) -C kernel dash-debug

code: all
	$(MAKE) -C kernel code

dump: all
	$(MAKE) -C kernel dump

clean:
	for dir in $(SUB); do \
		$(MAKE) -C $$dir clean; \
	done
