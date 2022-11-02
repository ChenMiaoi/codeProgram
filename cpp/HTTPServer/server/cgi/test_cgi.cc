#include <iostream>
#include <cstdlib>
#include <unistd.h>

bool GetQueryString(std::string& query_string) {
    bool result = false;
    std::cerr << "Debug METHOD: " << getenv("METHOD") << std::endl;
    std::string method = getenv("METHOD");
    if (method == "GET") {
        query_string = getenv("QUERY_STRING");
        result = true;
    }else if (method == "POST"){
        //CGI如何知道从标准输入中获取多少字节?
        int content_length = atoi(getenv("CONTENT_LENGTH"));
        char c = 0;
        while (content_length--) {
            read(0, &c, 1);
            query_string.push_back(c);
        }
        //std::cout << "DEBUG: Query_String: " << query_string << std::endl;
        result = true;
    }else {
        result = false;
    }
    return result;
}

void CutString(std::string& in, std::string& out1, std::string& out2, const std::string& sep) {
    auto pos = in.find(sep);
    if (std::string::npos != pos) {
        out1 = in.substr(0, pos);
        out2 = in.substr(pos + sep.size());
    }
}

int main() {
    std::string query_string;
    GetQueryString(query_string);
    std::string str1, str2;
    CutString(query_string, str1, str2, "&");
    std::string name1, value1;
    CutString(str1, name1, value1, "=");
    std::string name2, value2;
    CutString(str2, name2, value2, "=");

    //通过标准输出来传递回数据
    std::cout << name1 << " : " << value1 << std::endl;
    std::cout << name2 << " : " << value2 << std::endl;

    std::cerr << name1 << " : " << value1 << std::endl;
    std::cerr << name2 << " : " << value2 << std::endl;

    std::cout << value1 << " / " << value2 << " = " << atoi(value1.c_str()) / atoi(value2.c_str()) << std::endl;
    return 0;
}