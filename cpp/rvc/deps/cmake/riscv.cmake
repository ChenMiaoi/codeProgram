set(RISCV_EXEC "qemu-riscv32")
find_program(RISCV_EXEC_PATH ${RISCV_EXEC})
if(NOT RISCV_EXEC_PATH)
    message(WARNING "no qemu-riscv32 found. Please check package installation")
    set(RISCV_EXEC "echo WARN: unable to run")
endif()

set(ENV{RISCV_EXEC} "${RISCV_EXEC}")

set(RISCV_SPECIFIC_DEFS
    "/* target: RISCV */\n"
    "#define ARCH_PREDEFINED \"__riscv\" /* Older versions of the GCC toolchain defined __riscv__ */\n"
    "#define ELF_MACHINE 0xf3\n"
    "#define ELF_FLAGS 0\n"
)

if (ENABLE_RISCV) 
    # configure_file(${RISCV_SPECIFIC_DEFS} config)
    file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/config ${RISCV_SPECIFIC_DEFS})
endif()