OUTPUT_ARCH(riscv)
ENTRY(_start)
BASE_ADDRESS = 0x80200000;

SECTIONS {
    . = BASE_ADDRESS;
    start_kernel = .;

    start_text = .;
    .text : {
        *(.text.entry)
        . = ALIGN(4K);
        strampoline = .;
        *(.text.trampoline);
        . = ALIGN(4K);
        *(.text .text.*)
    }

    . = ALIGN(4K);
    end_text = .;
    start_rodata = .;
    .rodata : {
        *(.rodata .rodata.*)
        *(.start_rodata .start_rodata.*)
    }

    . = ALIGN(4K);
    end_rodata = .;
    start_data = .;
    .data : {
        *(.data .data.*)
        *(.start_data .start_data.*)
    }

    . = ALIGN(4K);
    end_data = .;
    start_bss_with_stack = .;
    .bss : {
        *(.bss.stack)
        start_bss = .;
        *(.bss .bss.*)
        *(.start_bss .start_bss.*)
    }

    . = ALIGN(4K);
    end_bss = .;
    end_kernel = .;

    /DISCARD/ : {
        *(.eh_frame)
    }
}