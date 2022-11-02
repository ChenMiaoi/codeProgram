#ifndef HTTPSERVER_PROTOCOL_HPP
#define HTTPSERVER_PROTOCOL_HPP

#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <sys/wait.h>
#include "../src/Util.hpp"
#include "../src/Log.hpp"

//分隔符
#define SEP ": "
#define LINE_END "\r\n"
//WebRoot
#define WEB_ROOT "../wwwroot"
#define HOME_PAGE "index.html"
#define PAGE_404 "../wwwroot/page404.html"
#define PAGE_400 "../wwwroot/page400.html"
#define PAGE_500 "../wwwroot/page500.html"
//状态码
#define OK 200
#define BAD_REQUEST 400
#define NOT_FOUND 404
#define SERVER_ERROR 500
//HTTP版本
#define HTTP_VERSION "HTTP/1.0"

static std::string Code2Desc(int code) {
    std::string desc;
    switch (code) {
        case 200: desc = "OK";
            break;
        case 404: desc = "Not Found";
            break;
        default:
            break;
    }
    return desc;
}

static std::string Suffx2Desc(const std::string& suffix) {
    static std::unordered_map<std::string, std::string> suffix2desc = {
            {".html", "text/html"},
            {".css" , "text/css"},
            {".js"  , "application/javascript"},
            {".jpg" , "application/x-jpg"},
            {".png" , "application/x-png"},
            {".xml" , "application/xml"},
            {".woff", "application/font-woff"}
    };

    auto iter = suffix2desc.find(suffix);
    if (iter != suffix2desc.end()) {
        return iter->second;
    }
    return "text/html";
}

class HTTPRequest {
public:
    HTTPRequest() : _content_length(0), _cgi(false) {}
    ~HTTPRequest() {}
public:
    std::string _request_line;
    std::vector<std::string> _request_header;
    std::string _blank;
    std::string _request_body;

    //解析完毕的结果
    std::string _method;
    std::string _uri;
    std::string _version;

    std::unordered_map<std::string, std::string> _header_kv;
    int _content_length;
    std::string _path;
    std::string _suffx;
    std::string _query_string;

    //CGI标志位
    bool _cgi;
    int _size;
};

class HTTPResponse {
public:
    HTTPResponse() : _blank(LINE_END), _status_code(OK), _fd(-1) {}
    ~HTTPResponse() {}
public:
    std::string _status_line;
    std::vector<std::string> _response_header;
    std::string _blank;
    std::string _response_body;

    int _status_code;
    int _fd;
};

//读取请求，分析请求，构建相应。 基本IO通信
class EndPoint {
public:
    EndPoint(int sock) : _sock(sock), _stop(false) {}
    ~EndPoint() {}
public:
    bool IsStop() { return !_stop; }
public:
    void RecvHttpRequest() {
        if ((!RecvHttpRequestLine()) && (!RecvHttpRequestHeader())) { //recv success
            ParseHttpRequestLine();
            ParseHttpRequestHeader();
            RecvHttpRequestBody();
        }else { //recv error
        }
    }

    void BuildHttpResponse() {
        auto& code = _http_response._status_code;
        std::string path = _http_request._path;
        std::size_t found = 0;
        struct stat st;
        int size = 0;
        if (_http_request._method != "GET" && _http_request._method != "POST") { // 非法请求
            LOG(WARNING, "Method is Not Right, Method is " + _http_request._method);
            code = BAD_REQUEST;
            goto END;
        }// end if
        if (_http_request._method == "GET") { // URL传参
            auto pos = _http_request._uri.find('?');
            if (pos != std::string::npos) { // 处理URI
                Util::CutString(_http_request._uri, _http_request._path, _http_request._query_string, "?");
                _http_request._cgi = true;
            }else { // 说明没有额外参数
                _http_request._path = _http_request._uri;
            }// end if
        }else if (_http_request._method == "POST") { // 正文传参
            _http_request._cgi = true;
            _http_request._path = _http_request._uri;
        }else {
            //do nothing
        }// end if
        path = _http_request._path;
        _http_request._path = WEB_ROOT;
        _http_request._path += path;
        if (_http_request._path[_http_request._path.size() - 1] == '/') {
            _http_request._path += HOME_PAGE;
        }
        if (stat(_http_request._path.c_str(), &st) == 0) {
            //说明URI访问的资源是存在的
            if (S_ISDIR(st.st_mode)) {  //判断当前URI是否可以访问
                //说明请求的资源是一个目录，不被允许访问，需要处理，默认的目录下index.html
                _http_request._path += "/";
                _http_request._path += HOME_PAGE;
                stat(_http_request._path.c_str(), &st);
            }
            if ((st.st_mode & S_IXGRP) || (st.st_mode & S_IXUSR) || (st.st_mode & S_IXOTH)) {
                //说明请求的资源是一个可执行文件，需要特殊处理
                _http_request._cgi = true;
            }
            _http_request._size = st.st_size;
        }else {
            //说明URI访问的资源是不存在的，或许可以写一个错误页面
            std::string waring = _http_request._path;
            waring += " Not Found!";
            LOG(WARNING, waring);
            code = NOT_FOUND;
            goto END;
        }

        //后缀的提取
        found = _http_request._path.rfind(".");
        if (found == std::string::npos) {
            _http_request._suffx = ".html";
        }else {
            _http_request._suffx = _http_request._path.substr(found);
        }

        if (_http_request._cgi) { // CGI成立
            //ProcessCgi();
            code = ProcessCgi();
        }else {
            //1. 目标网页是存在的
            //2. 返回并不是单单返回网页，而且是要构建HTTP响应
            code = ProcessNoneCgi(); //简单的网页返回，返回静态网页
        }
        END: // goto end
        BuildHttpResponseHelper();
    }

    void SendHttpResponse() {
        send(_sock, _http_response._status_line.c_str(), _http_response._status_line.size(), 0);
        for (auto iter : _http_response._response_header) {
            send(_sock, iter.c_str(), iter.size(), 0);
        }
        send(_sock, _http_response._blank.c_str(), _http_response._blank.size(), 0);

        if (_http_request._cgi) {
            auto& response_body = _http_response._response_body;
            int size = 0;
            int total = 0;
            const char* start = response_body.c_str();
            while (total < response_body.size() && (size = send(_sock, start + total, response_body.size() - total, 0) > 0)) {
                total += size;
            }
        }else {
            std::cout << "..........." << _http_response._fd << std::endl;
            std::cout << "..........." << _http_request._size << std::endl;
            sendfile(_sock, _http_response._fd, nullptr, _http_request._size);
            close(_http_response._fd);
        }
    }
private:
    bool RecvHttpRequestLine() {
        if (Util::ReadLine(_sock, _http_request._request_line) > 0) {
            _http_request._request_line.resize(_http_request._request_line.size() - 1);
            LOG(INFO, _http_request._request_line);
        }else {
            _stop = true;
        }
        return _stop;
    }

    bool RecvHttpRequestHeader() {
        std::string line;
        while (true) {
            line.clear();
            if (Util::ReadLine(_sock, line) <= 0) {
                _stop = true;
                break;
            }
            if (line == "\n") {
                break;
            }
            line.resize(line.size() - 1);
            _http_request._request_header.push_back(line);
            // LOG(INFO, line);
        }// end while
        if (line == "\n") {
            _http_request._blank = line;
        }
        return _stop;
    }

    void ParseHttpRequestLine() {
        auto& line = _http_request._request_line;

        std::stringstream ss(line);
        ss >> _http_request._method >> _http_request._uri >> _http_request._version;
        auto& method = _http_request._method;
        std::transform(method.begin(), method.end(), method.begin(), ::toupper);
        //LOG(INFO, _http_request._method);
        //LOG(INFO, _http_request._uri);
        //LOG(INFO, _http_request._version);
    }

    void ParseHttpRequestHeader() {
        std::string key;
        std::string value;
        for (auto& iter : _http_request._request_header) {
            if (Util::CutString(iter, key, value, SEP)) {
                _http_request._header_kv.insert({key, value});
            }
            //LOG(L_DEBUG, key);
            //LOG(L_DEBUG, value);
        }
    }

    bool IsNeedRecvHttpRequestBody() {
        auto method = _http_request._method;
        if (method == "POST") {
            auto& header_kv = _http_request._header_kv;
            auto iter = header_kv.find("Content-Length");
            if (iter != header_kv.end()) {
                _http_request._content_length = atoi(iter->second.c_str());
                return true;
            }// end if
        }// end if
        return false;
    }

    bool RecvHttpRequestBody() {
        if (IsNeedRecvHttpRequestBody()) {
            int content_length = _http_request._content_length;
            auto& body = _http_request._request_body;

            char ch = 0;
            while (content_length) {
                ssize_t s = recv(_sock, &ch, 1, 0);
                if (s > 0) {
                    body.push_back(ch);
                    content_length--;
                }else {
                    _stop = true;
                    break;
                }// end if
            }
        }// end if
        return _stop;
    }

    int ProcessNoneCgi() {
        _http_response._fd = open(_http_request._path.c_str(), 0, O_RDONLY);
        if (_http_response._fd >= 0) {
            return OK;
        }
        return NOT_FOUND;
    }

    int ProcessCgi() {
        int code = OK;
        //父进程数据
        auto& method = _http_request._method;
        auto& query_string = _http_request._query_string; // GET
        auto& request_body = _http_request._request_body; // POST
        auto& bin = _http_request._path; // 需要让子进程执行的目标程序，且一定存在
        int content_length = _http_request._content_length;
        auto& response_body = _http_response._response_body;

        std::string query_string_env;
        std::string method_env;
        std::string content_length_env;
        //约定，进程间通讯完全站在父进程的角度
        int input[2], output[2];

        if (pipe(input) < 0) {
            LOG(ERROR, "ProcessCgi input pipe create error!");
            code = SERVER_ERROR;
            return code;
        }
        if (pipe(output) < 0) {
            LOG(ERROR, "ProcessCgi output pipe create error!");
            code = SERVER_ERROR;
            return code;
        }
        //新线程进入，但只有一个进程
        pid_t pid = fork();
        if (pid == 0) { // child
            close(input[0]);
            close(output[1]);

            method_env = "METHOD=";
            method_env += method;
            putenv((char*)method_env.c_str());
            if (method == "GET") {
                query_string_env = "QUERY_STRING=";
                query_string_env += query_string;
                putenv((char*)query_string_env.c_str());
            }else if (method == "POST") {
                content_length_env = "CONTENT_LENGTH=";
                content_length_env += std::to_string(content_length);
                putenv((char*)content_length_env.c_str());
            }else {
                // do nothing
            }
            //exec*, 替换成功之后，目标子进程如何得知文件描述符呢, 不用知道，只用读0,或者写1即可
            //程序替换之后，数据没有了，但是曾经打开的PIPE还在。只替换代码数据和数据，并不替换内核进程相关的数据结构，例如：文件描述符表
            //约定：让目标被替换之后的进程，读取管道等价于读取标准输入，写入管道，等价于写到标准输出。在ecec*系列函数被执行前，进行重定向
            //站在子进程的角度
            //input[1]：写出
            //output[0]：读入
            dup2(output[0], 0);
            dup2(input[1], 1);
            execl(bin.c_str(), bin.c_str(), nullptr);
            exit(1);
        }else if (pid < 0) { // error
            LOG(ERROR, "ProcessCgi fork error!");
            code = SERVER_ERROR;
            return code;
        }else { // parent
            close(input[1]);
            close(output[0]);

            if (method == "POST") {
                const char* start = request_body.c_str();
                int total = 0;
                int size = 0;
                while (total < content_length && (size = write(output[1], start + total, request_body.size() - total)) > 0) {
                        total += size;
                }
            }

            int status = 0;
            char ch = 0;
            while (read(input[0], &ch, 1) > 0) {
                response_body.push_back(ch);
            }
            pid_t ret = waitpid(pid, &status, 0);
            if (ret == pid) {
                if (WIFEXITED(status)) {
                    if (WEXITSTATUS(status) == 0) {
                        code = OK;
                    }else {
                        code = BAD_REQUEST;
                    }
                }else {
                    code = SERVER_ERROR;
                }
            }

            close(input[0]);
            close(output[1]);
        }
        return code;
    }

    void HandlderError(const std::string page) {
        _http_request._cgi = false;
        //返回404页面
        _http_response._fd = open(page.c_str(), O_RDONLY);
        if (_http_response._fd > 0) {
            struct stat st;
            stat(page.c_str(), &st);
            _http_request._size = st.st_size;
            std::string line = "Content-type: text/html";
            line += LINE_END;
            _http_response._response_header.push_back(line);

            line = "Content-Length: ";
            line += std::to_string(st.st_size);
            line += LINE_END;
            _http_response._response_header.push_back(line);
        }
    }

    void BuildOkResponse() {
        std::string line = "Content-type: ";
        line += Suffx2Desc(_http_request._suffx);
        line += LINE_END;
        _http_response._response_header.push_back(line);
        line = "Content-Length: ";
        if (_http_request._cgi) {
            line += std::to_string(_http_response._response_body.size());
        }else {
            line += std::to_string(_http_request._size);
        }
        line += LINE_END;
        _http_response._response_header.push_back(line);
    }

    void BuildHttpResponseHelper() {
        auto& code = _http_response._status_code;
        auto& status_line = _http_response._status_line;
        status_line += HTTP_VERSION;
        status_line += " ";
        status_line += std::to_string(code);
        status_line += " ";
        status_line += Code2Desc(code);
        status_line += LINE_END;

        switch (code) {
            case OK:
                BuildOkResponse();
                break;
            case NOT_FOUND:
                HandlderError(PAGE_404);
                break;
            case BAD_REQUEST:
                HandlderError(PAGE_400);
                break;
            case SERVER_ERROR:
                HandlderError(PAGE_500);
                break;
            default:
                break;
        }
    }
private:
    int _sock;
    HTTPRequest _http_request;
    HTTPResponse _http_response;
    bool _stop;
};

//#define DEBUG 1

class CallBack {
public:
    CallBack() {}
    ~CallBack() {}
public:
    void operator() (int sock) {
        HandlerRequest(sock);
    }
public:
    void HandlerRequest(int sock) {
        LOG(INFO, "Hander Request Begin!");
#ifdef DEBUG
        // For test
        char buffer[4096];
        recv(sock, buffer, sizeof(buffer), 0);
        std::cout << "- - - - - - - - - - - - begin - - - - - - - - - - - - - -" << std::endl;
        std::cout << buffer << std::endl;
        std::cout << "- - - - - - - - - - - - end - - - - - - - - - - - - - -" << std::endl;
#else
        EndPoint* ep = new EndPoint(sock);
        ep->RecvHttpRequest();
        //ep->ParseHttpRequest();
        if (ep->IsStop()) {
            LOG(INFO, "Recv No Error, Build And Send");
            ep->BuildHttpResponse();
            ep->SendHttpResponse();
        }else {
            LOG(WARNING, "Recv Rrror, Stop And Send");
        }
        delete ep;
#endif
        LOG(INFO, "Hander Request End!");
    }
};

#endif //HTTPSERVER_PROTOCOL_HPP
