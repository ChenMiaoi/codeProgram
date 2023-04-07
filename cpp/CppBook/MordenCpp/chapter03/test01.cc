#include <iostream>

class shape {
public:
    virtual ~shape() = default;
};

class circle: public shape {
public:
    circle() { printf("circle()\n"); }
    ~circle() { printf("~circle()\n"); }
};

class triangle: public shape {
public:
    triangle() { printf("triangle()\n"); }
    ~triangle() { printf("~triangle()\n"); }
};

class result {
public:
    result() { printf("result()\n"); }
    ~result() { printf("~result()\n"); }
};

result process_shape(const shape& shape1, const shape& shape2) {
    printf("process_shape()\n");
    return result();
}

void foo(const shape&) {
	printf("foo(const shape&)\n");
}

void foo(shape&&) {
	printf("foo(shape&&)\n");
}

void bar(const shape& s) {
	printf("bar(const shape&)\n");
	foo(s);
}

void bar(shape&& s) {
	printf("bar(shape&&)\n");
	foo(s);
} 

int main() {
    printf("main()\n");
    result&& r =  process_shape(circle(), triangle());
    printf("something else\n");
    return 0;
}