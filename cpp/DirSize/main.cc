#include <iostream>
#include <sys/stat.h>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::cerr;

int main() {
    std::string root_path = "../TestDir";
    root_path += "/text.txt";
    struct stat _st;
    stat(root_path.c_str(), &_st);
    cout << _st.st_size;
    return 0;
}
