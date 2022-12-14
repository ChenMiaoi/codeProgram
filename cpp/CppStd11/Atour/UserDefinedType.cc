#include <iostream>

#if old_version
struct Vector {
    double* elem;
    int sz;
};

void vector_init(Vector& v, int s) {
    v.elem = new double[s];
    v.sz = s;
}

double read_and_sum(int s) {
	Vector v;
	vector_init(v, s);

	for (int i = 0; i !=s; ++i)
		std::cin >> v.elem[i];

	double sum = 0;
	for (int i = 0; i != s; ++i)
		sum += v.elem[i];
	return sum;
}

void f(Vector& v, Vector& rv, Vector* pv) {
    int i1 = v.sz;
    int i2 = rv.sz;
    int i3 = pv->sz;
}
#endif // old_version of Vector

class Vector {
public:
    Vector(int s): elem{new double[s]}, sz{s} {}
    double& operator[] (int i) { return elem[i]; }
    int size() { return sz; }
private:
    double* elem;
    int sz;
};

enum class Color {
    red,
    blue,
    green
};

enum class Traffic_light {
    green,
    yellow,
    red
};

Traffic_light& operator++ (Traffic_light& t) { // prefix increment: ++Color
    switch (t) {
        case Traffic_light::green: return t = Traffic_light::yellow;
        case Traffic_light::yellow: return t = Traffic_light::red;
        case Traffic_light::red: return t = Traffic_light::green;
    }
}

#if simple_version
Traffic_light& operator++ (Traffic_light& t) { // prefix increment: ++Color
    using enum Traffic_light;
    switch (t) {
        case green: return t = yellow;
        case yellow: return t = red;
        case red: return t = green;
    }
}
#endif // simple_version

enum Color_1 {
    red,
    green,
    blue
};

enum class Type { // a Type can hold values ptr and num
    ptr,
    num
};

union Value {
    double* p;
    int i;
};

#if old_version
struct Entry {
    std::string name;
    Type t;
    double* p; // use p if t == Type::ptr
    int i;  // use i if t == Type::num
};

void f(Entry* pe) {
    if (pe->t == Type::num)
        std::cout << pe->i;
    else if (pe->t == Type::ptr)
        std::cout << pe->p;
}
#endif // old_version

struct Entry {
    std::string name;
    Type t;
    Value v;
};

void f(Entry* pe) {
    if (pe->t == Type::ptr)
        std::cout << pe->v.p;
    else
        std::cout << pe->v.i;
}

int main() {
    Color col = Color::red;
    Traffic_light light = Traffic_light::red;
    auto signal = Traffic_light::red;
    Traffic_light next = ++signal;

    int col_1 = Color_1::green;

    return 0;
}