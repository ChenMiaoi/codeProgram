#include <iostream>
#include <list>
#include <vector>
#include <complex>
#include <string>

template <typename T>
class Vector {
public:
    explicit Vector(int s); // constructor: establish invariant, acquire resources
    Vector(std::initializer_list<T> li);
    ~Vector() { delete[] elem; } // destructor: release resources
public:
    T* begin();
    T* begin() const;
    T* end();
    T* end() const;

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

//void func2() {
//    using namespace std::literals::string_literals;
//    Vector<std::string> vs {"Hello", "World"};
//    Vector vs1 {"Hello", "World"};
//    Vector vs2 {"Hello"s, "World"s};
//    // Vector vs3 {"Hello"s, "World"};
//    Vector<std::string> vs4 {"Hello"s, "World"};
//}

//template <typename Sequence, typename Value>
//Value sum (const Sequence& s, Value v) {
//    for (auto x : s)
//        v += x;
//    return v;
//}

//void user(Vector<int>& vi, std::list<double>& ld,
//          std::vector<std::complex<double>>& vc) {
//    int x = sum(vi, 0); // the sum of a vector of ints (add ints)
//    double d = sum(vi, 0.0); // the sum of a vector of ints (add doubles)
//    double dd = sum(ld, 0.0); // the sum of a list of doubles
//    auto z = sum(vc, std::complex {0.0, 0.0});
//    // the sum of a vector of complex<double>
//}

template <typename T>
class Less_than {
    const T val; // value to compare against
public:
    Less_than(const T& v): val(v) {}
    bool operator() (const T& x) const { return x < val; } // call operator
};

void func3() {
    Less_than lti {42}; // lti(i) will compare i to 42 using < (i<42)
    using namespace std::literals::string_literals;
    Less_than lts {"Backus"s}; // lts(s) will compare s to "Backus" using < (s<"Backus")
    Less_than<std::string> lts2 {"Naur"}; // "Naur" is a C-style string, so we need <string> to get the right <
}

void fct(int n, const std::string& s) {
    Less_than lti {42};
    using namespace std::literals::string_literals;
    Less_than lts {"Backus"s};
    Less_than<std::string> lts2 {"Naur"};
    bool b1 = lti(n); // true if n < 42
    bool b2 = lts(s); // true is s < "Backus"
}

//void f(const Vector<int>& vec, const std::list<std::string>& lst, int x, const std::string& s) {
//    std::cout << "number of values less than " << x << " : " << std::count(vec.begin(), Less_than {x}) << "\n";
//    std::cout << "number of values less than " << s << " : " << std::count(lst, Less_than {x});
//}

//void f(const Vector<int>& vec, const std::list<std::string>& lst, int x, const std::string& s) {
//    std::cout << "number of values less than "
//                << x << " : "
//                << std::count(vec.begin(), [&](int a) { return a < x; })
//                << "\n";
//    std::cout << "number of values less than "
//                << s << " : "
//              << std::count(lst, [&](const std::string& a) { return a < s; });
//}

class X {
public:
    void f(X& x) {
        auto f = [this]() { return *this; };
        auto f1 = [*this](){ return *this; };
    }
};

enum class Init_mode {
    zero,
    seq,
    cpy,
    patrn
}; // initializer alternatives

//void user(Init_mode m, int n, std::vector<int>& arg, Iterator p, Iterator q) {
//    std::vector<int> v;
//
//    switch (m) {
//        case Init_mode::zero:
//            v = std::vector<int> (n);
//            break;
//        case Init_mode::cpy:
//            v = arg;
//            break;
//    }
//
//    if (m == Init_mode::seq)
//        v.assign(p, q);
//}

//void user(Init_mode m, int n, std::vector<int>& arg, Iterator p, Iterator q) {
//    std::vector<int> v = [&] {
//        switch (m) {
//            case Init_mode::zero:
//                return std::vector<int> (n);
//            case Init_mode::seq:
//                return std::vector<int> {p, q};
//            case Init_mode::cpy:
//                return arg;
//            case Init_mode::patrn:
//                break;
//        }
//    }();
//}

template <class F>
struct Final_action {
    explicit Final_action(F f): act(f) {}
    ~Final_action() { act(); }
    F act;
};

template <class F>
[[nodiscard]] auto finally(F f) {
    return Final_action {f};
}

void old_type (int n) {
    void* p = (void*) malloc(n * sizeof (int )); // C-type
    auto act = finally([&]{ free(p); }); // call the lambda upon scope exit
}// p is implicitly freed upon scope exit

[[nodiscard("The empty return value must be used")]]
bool empty() {
    return false;
}

int main() {
    // func1();
    // old_type(1);
    empty();
    return 0;
}