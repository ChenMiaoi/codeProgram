#ifndef HTTPSERVER_UTIL_HPP
#define HTTPSERVER_UTIL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "Log.hpp"

// 工具类
class Util {
public:
    static int ReadLine(int sock, std::string& out) {
        char ch = 'X';
        while (ch != '\n') {
            ssize_t s = recv(sock, &ch, 1, 0);
            if (s > 0) {
                if (ch == '\r') { // \r -> \n or \r\n -> \n
                    //查看\r后面的内容，只是查看，而不取走，使用recv选项MSG_PEEK
                    recv(sock, &ch, 1, MSG_PEEK);
                    if (ch == '\n') {
                        recv(sock, &ch, 1, 0); // 如果存在，那么就直接取走了
                    }else { // 此时ch == \r
                        ch = '\n';
                    }// end if
                }// end if
                //1. 普通 //2. \n
                out.push_back(ch);
            }else if (s == 0){
                return 0;
            }else {
                return -1;
            }// end if
        }// end while
        return out.size();
    }// end ReadLine

    static bool CutString(const std::string& target, std::string& sub1_out, std::string& sub2_out, const std::string& sep) {
        size_t pos = target.find(sep);
        if (pos != std::string::npos) {
            sub1_out = target.substr(0, pos);
            sub2_out = target.substr(pos + sep.size());
            // LOG(INFO, "CutString ... success!");
            return true;
        }else {
            LOG(ERROR, "CutString error!");
            return false;
        }
    }

    static bool GetUrl(std::string& url, std::unordered_map<std::string, std::string>& out) {
        std::string sep = "&";
        std::vector<std::string> v;
        int count = 0;
        size_t pos = 0;
        std::string out1, out2;
        for (auto e : url) { if (e == '&') { count++; } }
        while ((pos = url.find(sep)) != std::string::npos) {
            out1 = url.substr(0, pos);
            out2 = url.substr(pos + sep.size());
            url = out2;
            v.emplace_back(out1);
            if (--count == 0) {
                v.emplace_back(out2);
                break;
            }
        }
        for (auto e : v) {
            CutString(e, out1, out2, "=");
            out.emplace(make_pair(out1, out2));
        }
        return true;
    }

    static bool GetQueryString(std::string& query_string) {
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
};

#endif //HTTPSERVER_UTIL_HPP
