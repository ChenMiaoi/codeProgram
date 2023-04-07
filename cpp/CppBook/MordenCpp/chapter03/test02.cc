#include <iostream>

class Obj {
public:
	Obj() { std::cout << "Obj()" << std::endl; }
	Obj(const Obj&) {
		std::cout << "Obj(const Obj&)" << std::endl;
	}
	Obj(Obj&&) {
		std::cout << "Obj(Obj&&)" << std::endl;
	}
};

Obj simple() {
	Obj obj;
	return obj;
}

Obj simple_with_move() {
	Obj obj;
	return std::move(obj);
}

Obj complicated(int n) {
	Obj obj1;
	Obj obj2;
	// 如果有分支，那么编译器大多数情况不会进行NRVO优化
	if (n % 2 == 0) {
		return obj1;
	} else {
		return obj2;
	}
}

int main() {
	std::cout << "*** 1 ***" << std::endl;
	auto obj1 = simple();
	std::cout << "*** 2 ***" << std::endl;
	auto obj2 = simple_with_move();
	std::cout << "*** 3 ***" << std::endl;
	auto obj3 = complicated(42);
	return 0;
}