#include "Vector.h"

Vector::Vector() {}

Vector::Vector(int s) {
    if (s < 0)
        throw std::length_error {"Vector constructor: negative size"};
    if ((elem = new double[s]) == nullptr)
        throw std::bad_alloc {};
    sz = s;
}

#if old_version
double &Vector::operator[](int i) {
    if (!(0 < i && i < size()))
        throw std::out_of_range {"Vector::operaor[]()"};
    return elem[i];
}
#endif // old_version

enum class Error_action { // error-handing alternatives
    ignore,
    throwing,
    terminating,
    logging
};

// a default
constexpr Error_action default_Error_action = Error_action::throwing;

enum class Error_code {
    range_error,
    length_error
};

std::string error_code_name[] {"range error", "length error"};

template <Error_action action = default_Error_action, class C>
constexpr void except(C cond, Error_code x) { // take "action" if the expected condition "cond" doesn't hold
    if constexpr (action == Error_action::logging)
        if (!cond())
            std::cerr << "expect() failure: " << int(x) << ' ' << error_code_name[int(x)] << "\n";

    if constexpr (action == Error_action::throwing)
        if (!cond())
            throw x;

    if constexpr (action == Error_action::terminating)
        if (!cond())
            std::terminate();
}

double &Vector::operator[](int i) {
    except([i, this]() -> bool { return 0 <= i && i < size(); }, Error_code::range_error);
    return elem[i];
}

int Vector::size() {
    return sz;
}