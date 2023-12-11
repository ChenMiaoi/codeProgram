#include "os.h"
#include <stdarg.h>

// static _printint(char*)

static int _vsnprintf(char* out, size_t n, const char* fmt, va_list vl) {
    int format = 0, longarg = 0;
    size_t pos = 0;

    for (; *fmt; fmt++) {
        if (format) {
            switch (*fmt) {
            case 'l': { 
                longarg = 1; break;
            }
            case 'p': {
                longarg = 1;
                /* 添加0x前缀 */
                if (out && pos < n) out[pos] = '0';
                pos++;
                if (out && pos < n) out[pos] = 'x';
            }
            case 'x': {
                /* 添加0x前缀 */
                if (out && pos < n) out[pos] = '0';
                pos++;
                if (out && pos < n) out[pos] = 'x';
                pos++;
                
                long num = longarg ? va_arg(vl, long) : va_arg(vl, int);
                int hex_digits = 2 * (longarg ? sizeof(long) : sizeof(int)) - 1;
                for (int i = hex_digits; i >= 0; i--) {
                    int d = (num >> (4 * i)) & 0xF;
                    if (out && pos < n) out[pos] = (d < 10 ? '0' + d : 'a' + d - 10);
                    pos++;
                }
                longarg = 0;
                format  = 0;
                break;
            }
            case 'd': {
                long num = longarg ? va_arg(vl, long) : va_arg(vl, int);
                /* 处理负数的情况 */
                if (num < 0) {
                    num = -num;
                    /* 添加负号后，按照正数处理 */
                    if (out && pos < n) out[pos] = '-';
                    pos++;
                }

                long digits = 1;
                for (long t = num; t /= 10; digits++);
                for (int i = digits - 1; i >= 0; i--, num /= 10) {
                    if (out && pos + i < n) out[pos + i] = '0' + (num % 10);
                }
                pos += digits;
                longarg = 0;
                format = 0;
                break;
            }
            case 's': {
                const char* s = va_arg(vl, const char*);
                while (*s) {
                    if (out && pos < n) out[pos] = *s;
                    pos++, s++;
                }
                longarg = 0;
                format  = 0;
                break;
            }
            case 'c': {
                if (out && pos < n) out[pos] = (char)va_arg(vl, int);
                pos++;
                longarg = 0;
                format  = 0;
                break;
            }
            default:
                break;
            }
        } else if (*fmt == '%') {
            format = 1;
        } else {
            if (out && pos < n) {
                out[pos] = *fmt;
            }
            pos++;
        }
    }
    if (out && pos < n) {
        out[pos] = '\0';
    } else if (out && n) {
        out[n - 1] = '\0';
    }

    return pos;
}

static char print_buf[1024];

static int _vprintf(const char* fmt, va_list vl) {
    int res = _vsnprintf(NULL, -1, fmt, vl);
    if (res + 1 >= sizeof(print_buf)) {
        uart_puts("error: output string size overflow\n");
        while (1);
    }
    _vsnprintf(print_buf, res + 1, fmt, vl);
    uart_puts(print_buf);

    return res;
}

int printf(const char* fmt, ...) {
    int res = 0;
    va_list vl;
    va_start(vl, fmt);
    res = _vprintf(fmt, vl);
    va_end(vl);

    return res;
}

void panic(const char* s) {
    (void)printf("panic: ");
    (void)printf(s);
    (void)printf("\n");

    while (1);
}