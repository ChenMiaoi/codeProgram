cmake_minimum_required(VERSION 3.2)
project(rvos VERSION 0.1.0  LANGUAGES C ASM)

set(QEMU qemu-system-riscv32)
set(QEMU_FLAGS "-nographic -smp 1 -machine virt -bios none -kernel os.elf -s -S &")
set(CMAKE_C_COMPILER riscv64-unknown-elf-gcc)
set(CMAKE_C_FLAGS "-nostdlib -fno-builtin -march=rv32ima -mabi=ilp32 -g")
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_ASM_FLAGS  ${CMAKE_C_FLAGS})

# source file
set(SRCS_ASM
    start.S mem.S switch.S
)

set(SRCS_C
    kernel.c uart.c printf.c mm.c
)

# generate obj
foreach (SRC ${SRCS_ASM})
    get_filename_component(SRC_NAME ${SRC} NAME_WE)
    add_custom_command(
        OUTPUT ${SRC_NAME}.o
        COMMAND ${CMAKE_ASM_COMPILER} ${CMAKE_ASM_FLAGS} -c -o ${SRC_NAME}.o ${CMAKE_CURRENT_SOURCE_DIR}/${SRC}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${SRC}
    )
    list(APPEND OBJS ${SRC_NAME}.o)
endforeach ()

foreach (SRC ${SRCS_C})
    get_filename_component(SRC_NAME ${SRC} NAME_WE)
    add_custom_command(
        OUTPUT ${SRC_NAME}.o
        COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} -c -o ${SRC_NAME}.o ${CMAKE_CURRENT_SOURCE_DIR}/${SRC}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${SRC}
    )
    list(APPEND OBJS ${SRC_NAME}.o)
endforeach ()

# generate target
add_executable(os.elf ${OBJS})
target_link_options(os.elf PRIVATE -T os.ld)
target_compile_options(os.elf PRIVATE ${CMAKE_C_FLAGS})