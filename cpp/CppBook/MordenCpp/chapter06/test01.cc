#include <iostream>
#include <vector>
#include <iterator>

class matrix {
    friend matrix operator* (const matrix&, const matrix&);
public:
    matrix(size_t nrows, size_t ncols): _nrows(nrows), _ncols(ncols) {
        _data = new float [ncols * nrows];
    }
    ~matrix() { delete[] _data; }
private:
    float* _data;
    size_t _nrows;
    size_t _ncols;
};

matrix operator* (const matrix& lhs, const matrix& rhs) {
    if (lhs._ncols != rhs._ncols)
        throw std::runtime_error("matrix sizes mismatch");
    matrix result(lhs._nrows, rhs._ncols);
    return result;
}

int main() {
    std::vector<int> v1 {1, 2, 3, 4, 5};
    std::vector<int> v2;
    std::copy(v1.begin(), v1.end(), std::back_inserter(v2));


    return 0;
}