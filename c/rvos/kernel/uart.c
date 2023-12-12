#include "os.h"
#include "platform.h"
#include "types.h"

/**
 * Reference
 * [1]: TECHNICAL DATA ON 16550, http://byterunner.com/16550.html
 */

 /**
  * UART的控制寄存器映射在UART0的物理地址中
  * 该宏函数通过访问地址获取控制寄存器
  */
#define UART_REG(reg) ((volatile uint8_t*)(UART0 + reg))

/**
 * UART控制寄存器表， 参考 [1] "PROGRAMMING TABLE"
 * @note 一些寄存器有重用功能
 * 0 (write mode): THR/DLL
 * 1 (write mode): IER/DLM
 */
#define RHR 0	// Receive Holding Register (read mode)
#define THR 0	// Transmit Holding Register (write mode)
#define DLL 0	// LSB of Divisor Latch (write mode)
#define IER 1	// Interrupt Enable Register (write mode)
#define DLM 1	// MSB of Divisor Latch (write mode)
#define FCR 2	// FIFO Control Register (write mode)
#define ISR 2	// Interrupt Status Register (read mode)
#define LCR 3	// Line Control Register
#define MCR 4	// Modem Control Register
#define LSR 5	// Line Status Register
#define MSR 6	// Modem Status Register
#define SPR 7	// ScratchPad Register

/**
 * LSR(Line Status Register)提供数据传输到CPU的状态
 * 
 * LSR BIT 0:
 * 0 = RHR寄存器或`FIFO`中没有数据
 * 1 = 数据已经被接收且保存在RHR寄存器或`FIFO`中
 * LSR BIT 1:
 * 0 = no overrun erro (normal)
 * 1 = overrun error. 
        在RHR被清空之前，或者如果`FIFO`（先进先出缓冲区）被启用，则仅在`FIFO`已满且下一个字符已完全接收到移位寄存器后，
        溢出错误才会发生。请注意，移位寄存器中的字符会被覆盖，但不会被传输到`FIFO`中.
 * LSR BIT 2(奇偶校验错误):
 * 0 = no parity error (normal)
 * 1 = parity error. Receive data does not have correct parity information.
 * LSR BIT 3(帧错误):
 * 0 = no framing error (normal)
 * 1 = framing error received. Received data did not have a valid stop bit.
 * LSR BIT 4:
 * 0 = no break condition (normal)
 * 1 = receiver received a break signal (RX was low for one character time frame).
 * LSR BIT 5:
 * 0 = transmit holding register is full. 16550 will not accept any data for transmission.
 * 1 = transmitter hold register (or FIFO) is empty. CPU can load the next character.
 * LSR BIT 6:
 * 0 = transmitter holding and shift registers are full.
 * 1 = transmit holding register is empty. In FIFO mode this bit is set to one whenever the the transmitter FIFO and 
        transmit shift register are empty.
 * LSR BIT 7:
 * 0 = normal
 * 1 = At least one parity error, framing error or break indicator is in the FIFO. Cleared when LSR is read.
 */

#define LSR_RX_READY (1 << 0)
#define LSR_TX_IDLE  (1 << 5)

#define uart_read_reg(reg) (*(UART_REG(reg)))
#define uart_write_reg(reg, val) (*(UART_REG(reg)) = (val))

/**
 * UART初始化函数  
 *
 * 在初始化中，我们需要设置波特率，而和波特率有关的寄存器为DLL和DLM；
 * 我们的目的是，当晶振频率为1.8432MHz的时候，波特率为38.4K，有以下对应表
        BAUD RATE  1.8432 MHZ clock  7.3728 MHZ clock
        50           2304               9216
        75           1536               6144
        110          1047               4188
        134.5         857               3428
        150           768               3072
        300           384               1536
        600           192                768
        1200           96                384
        2400           48                192
        3600           32                128
        4800           24                 96
        7200           16                 64
        9600           12                 48
        19.2K           6                 24
        38.4K           3                 12
        57.6K           2                  8
        115.2K          1                  4
        230.4K       not possible          2
        460.8K       not possible          1
 * 也就是说，我们需要将DL寄存器设置为0x0003，因为DL寄存器的高位和低位分别保存在DLM和DLL中
 * 因此DLM = 0x00, DLL = 0x03即可。
 * 需要注意的是，DL两个寄存器与RHR、THR、IER寄存器发生冲突，因此需要重定向选择位，与此有关的为LCR寄存器
 * LCR(Line Control Register)于指定异步数据通信格式。字长、停止位和奇偶校验的数目可以通过在这个寄存器中写入适当的位来选择。
 * LCR BIT 1-0:
 * These two bits specify the word length to be transmitted or received.
    BIT-1   BIT-0  WORD LENGTH
      0       0         5
      0       1         6
      1       0         7
      1       1         8
 * LCR BIT 2:
 * The number of stop bits can be specified by this bit.
     BIT-2  WORD LENGTH STOP BITS(s)
       0       5,6,7,8      1
       1       5            1.5
       1       6,7,8        2
 * LCR BIT 3:
 * Parity or no parity can be selected via this bit.
 * BIT-3 PARITY
 * 0 None
 * 1 Parity is both generated on transmission and checked on receive.
 * LCR BIT 4:
 * If parity (LCR-3) is enabled. LCR BIT 4 selects the even or odd format.
 * BIT-4 PARITY
 * 0 ODD
 * 1 EVEN
 * Odd parity means that the character will always have an odd number of 1's, 
 * and even means it will always have an even number of 1's in the binary representation.
 * LCR BIT 5:
 * Force parity to always 1 or 0. When this bit is set to 1, then parity will always be 0 if LCR-4 is 1 and will be 1 if LCR-4 is 0.
 * LCR BIT 6:
 * Break control bit. It causes a break condition to be transmitted (the TX is forced to low state) when set to 1.
 *! LCR BIT 7:
 *! The internal baud rate counter latch enable (DLAB).
 *! BIT 7 BAUD LATCH
 *! 0 disabled, normal operation
 *! 1 enabled
 */
void uart_init() {
    /* 关中断 */
    uart_write_reg(IER, 0x00);

    /* 第七位是设置波特率启用 */
    uint8_t lcr = uart_read_reg(LCR);
    uart_write_reg(LCR, lcr | (1 << 7));
    uart_write_reg(DLM, 0x00);
    uart_write_reg(DLL, 0x03);

    /**
     * 清空上述flag后再次配置
     * - 设置数据字长为8 bit，且停止位为1 bit
     * - 无奇偶校验位
     * - 无中断控制位
     * - 关闭波特率启用
     */
    lcr = 0;
    uart_write_reg(LCR, lcr | (3 << 0));

	/**
	 * 开启接收中断使能
	 */
	uint8_t ier = uart_read_reg(IER);
	uart_write_reg(IER, ier | (1 << 0));
}

/**
 * 向uart设备传输一个字符
 * 
 * @param c 想要传输的字符
 * @return int 
 */
int uart_putc(char c) {
	/* 当LSR的第五位被设置为1时，就说明THR或`FIFO`当前为空，可以接受信息 */
	while ((uart_read_reg(LSR) & LSR_TX_IDLE) == 0);
	return uart_write_reg(THR, c);
}

/**
 * 向uart设备传输一个字符串
 * 
 * @param s 想要传输的字符串
 */
void uart_puts(char* s) {
	while (*s) {
		(void)uart_putc(*s++);
	}
}

/**
 * 向uart缓冲区中读取一个字符
 * 
 * @return int 返回读取到的字符
 */
int uart_getc(void) {
	if (uart_read_reg(LSR) & LSR_RX_READY) 
		return uart_read_reg(RHR);
	else
		return -1;
}

/**
 * 测试uart外部中断调用
 */
void uart_isr() {
	while (1) {
		int c= uart_getc();
		if (c == -1) break;
		else {
			uart_putc((char)c);
			uart_putc('\n');
		}
	}
}