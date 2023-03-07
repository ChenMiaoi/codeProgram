#include <iostream>
#include <string>
#include <stack>

using __register_t = char;
struct __register {
    using type = __register_t;
    __register_t r0; __register_t r1;
    __register_t r2; __register_t r3;
    __register_t r4; __register_t r5;
    __register_t r6; __register_t r7;
    __register_t r8; __register_t r9;
    __register_t r10; __register_t r11;
    __register_t r12; __register_t r14;
    __register_t r15;
}__register_type;

struct __register_stat {
    using __stat_type = bool;
    __stat_type Z; __stat_type N;
    __stat_type C; __stat_type V;
}__register_stat;

std::stack<__register_t> __r13;
void calc();
void math();
void new_ln();
void input();
void get_ch();
void write_ch();
void read_ch();

int main() {
    calc();
    return 0;
}

void calc() {
    new_ln();
    input();
    __register_type.r2 = __register_type.r0;
    __register_type.r3 = __register_type.r1;
    new_ln();
    input();
    __register_type.r4 = __register_type.r0;
    new_ln();
    math();
}

void math() {
    if (__register_type.r2 == '+') {
        __register_stat.Z = 1;
    }
    if (__register_stat.Z == 1) {
        __register_type.r1 = __register_type.r1 + __register_type.r3;
    }
    if (__register_type.r2 == '-') {
        __register_stat.Z = 1;
    }
    if (__register_stat.Z == 1) {
        __register_type.r1 = __register_type.r3 - __register_type.r1;
    }
    if (__register_type.r2 == '*') {
        __register_stat.Z = 1;
    }
    if (__register_stat.Z == 1) {
        __register_type.r4 = __register_type.r1;
        __register_type.r1 = __register_type.r1 * __register_type.r3;
    }
    __register_type.r15 = __register_type.r14;
}

void get_ch() {
    read_ch();
    __register_type.r15 = __register_type.r14;
}

void write_ch() {
    printf("%c", __register_type.r0);
}

void read_ch() {
    scanf("%c", &__register_type.r0);
    // __register_type.r0 =  getchar();
}

void input() {
    __register_type.r0 = 0;
    __register_type.r1 = (int)1;
next:
    __r13.push(__register_type.r14);
    get_ch();
    __register_type.r14 = __r13.top();
    __r13.pop();
    // if (__register_type.r0 == '0')
    //     __register_stat.Z = 1;
    if (__register_type.r0 < '0') { // because of my ability, I can't impl the total
        __register_stat.N = 1;
        __register_stat.V = 0;
    }
    if ((__register_stat.N == 1 && __register_stat.V == 0) ||
        (__register_stat.N == 0 && __register_stat.V == 1)) {
        __register_type.r15 = __register_type.r14;
        return;
    }
    if (__register_type.r0 > '9') {
        __register_stat.Z = 0;
        __register_stat.N = 1;
        __register_stat.V = 1;
    }
    if (__register_stat.Z == 0 && ((__register_stat.N == 1 && __register_stat.V == 1))) {
        __register_type.r15 = __register_type.r14;
        return;
    }
    __register_type.r0 = __register_type.r0 - 0x30;
    __register_type.r4 = __register_type.r1;
    __register_type.r5 = 10;
    __register_type.r1 = __register_type.r4 * __register_type.r5;
    __register_type.r1 = __register_type.r1 + __register_type.r0;
    goto next;
}

void new_ln() {
    __r13.push(__register_type.r0);
    __r13.push(__register_type.r14);
    __register_type.r0 = 0x0D;
    write_ch();
    __register_type.r0 = 0X0A;
    write_ch();
    __register_type.r15 = __r13.top();
    __r13.pop();
    __register_type.r0 = __r13.top();
    __r13.pop();
}

