#include <iostream>
#include <list>
#include <string>

template <typename T>
class Vector {
public:
    explicit Vector(int s); // constructor: establish invariant, acquire resources
    Vector(std::initializer_list<T> li);
    ~Vector() { delete[] elem; } // destructor: release resources
public:
    T* begin();
    T* end();

    // copy and move operations
    Vector(const Vector<T>& v);
    Vector(Vector<T>&& v);
    Vector<T>& operator= (const Vector<T>& v);
    Vector<T>& operator= (Vector<T>&& v);

    T& operator[] (int i); // for non-const Vectors
    const T& operator[] (int i) const; // for const Vectors
    int size() const { return sz; }
private:
    T* elem; // elem points to an array of sz elements of type T
    int sz;
};

template <typename T>
Vector<T>::Vector(int s) {
    if (s < 0)
        throw std::length_error {"Vector constructor: negative size"};
    elem = new T[s];
    sz = s;
}

template <typename T>
const T &Vector<T>::operator[](int i) const {
    if (i < 0 || size() <= i)
        throw std::out_of_range {"Vector::operator[]"};
    return elem[i];
}

template <typename T>
T *Vector<T>::begin() {
    return &elem[0];
}

template <typename T>
T *Vector<T>::end() {
    return &elem[size()];
}

void func1() {
    Vector<char> vc(200); // vector of 200 characters
    Vector<std::string> vs(17); // vector of 17 strings
    Vector<std::list<int>> vli(45); // vector of 45 lists of integers

    for (auto& v : vs)
        std::cout << v << " ";
}

template <typename T, int N>
struct Buffer {
    constexpr int size() { return N; }
    T elem[N];
};

template <char* s>
void outs() { std::cout << s; }

char arr[] = "Weird workaround";

void use() {
    // outs<"straightforward use">(); // error (for now)
    outs<arr>(); // OK
}

void func2() {
    using namespace std::literals::string_literals;
    Vector<std::string> vs {"Hello", "World"};
    Vector vs1 {"Hello", "World"};
    Vector vs2 {"Hello"s, "World"s};
    // Vector vs3 {"Hello"s, "World"};
    Vector<std::string> vs4 {"Hello"s, "World"};
}

int main() {
    func1();
    return 0;
}