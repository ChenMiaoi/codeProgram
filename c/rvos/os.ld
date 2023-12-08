/**
* ref https://sourceware.org/binutils/docs/ld/
*/

/* 指定输出架构 */
OUTPUT_ARCH("riscv")
/* 指定入口 */
ENTRY(_start)

/**
* ref https://sourceware.org/binutils/docs/ld/MEMORY.html
* 用于描述一个内存块的位置和大小
* @code
* MEMORY {
*   name [(attr)] : ORIGIN = origin, LENGTH = len
*   ...
* }
* @endcode
* 上面的每一行都能定义出一块独特的区域(不允许重名)，此处我们定义了`ram`内存区
* 而`attr`是一个可选的内存特殊标记，如果没有显示指定，则默认使用输入文件的标识
* `w`(writable)、`x`(executable)、`r`(readable)、`a`(allocatable)、`i`(initialized)
* @note `!`表示 invert，颠倒后面任何属性的意义
* 因此，我们在此处描述了一块从0x80000000开始长度为128M的可写可执行可分配只读已被初始化的`ram`内存
*/
MEMORY {
    ram(wax!ri) : ORIGIN = 0x80000000, LENGTH = 128M
}

/**
* ref https://sourceware.org/binutils/docs/ld/SECTIONS.html
* SECTIONS操作指明了输入文件如何映射到输出文件内存中的各个sections
*
* ref https://sourceware.org/binutils/docs/ld/PROVIDE.html
* PROVIDE关键字被用于定义一个符号， `.` = 当前内存位置
*/
SECTIONS {
    .text : {
        PROVIDE(_text_start = .);
        /* 在此处匹配所有输入文件的.text段，然后融合进入.text */
        *(.text .test.*)
        PROVIDE(_text_end = .);
    } > ram

    .rodata : {
        PROVIDE(_rodata_start = .);
        *(.rodata .rodata.*)
        PROVIDE(_rodata_end = .);
    } > ram

    .data : {
        /* 这里声明了，.data段是对齐4096KB的，因为我们的页表大小为4096KB */
        . = ALIGN(4096);
        PROVIDE(_data_start = .);

        /* .sdata不是一个标准的ELF段，常规下和.data一样，
            特殊情况用于存储特殊类型数据，比如大小端，数据对齐 */
        *(.sdata .sdata.*)
        *(.data .data.*)
        PROVIDE(_data_end = .);
    } > ram

    .bss : {
        PROVIDE(_bss_start = .);
        
        /* .sbss通常表示small bss */
        *(.sbss .sbss.*)
        *(.bss .bss.*)
        /**
         * ref https://sourceware.org/binutils/docs/ld/Input-Section-Common.html
         * COMMON符号用于一些不是那么特殊的数据段，未初始化变量
         */
        *(COMMON)
        PROVIDE(_bss_end = .);
    } > ram

    PROVIDE(_memory_start = ORIGIN(ram));
    PROVIDE(_memory_end = ORIGIN(ram) + LENGTH(ram));

    PROVIDE(_heap_start = _bss_end);
    PROVIDE(_heap_size = _memory_end - _heap_start);
}