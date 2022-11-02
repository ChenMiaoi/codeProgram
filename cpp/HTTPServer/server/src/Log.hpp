#ifndef HTTPSERVER_LOG_HPP
#define HTTPSERVER_LOG_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#define INFO    1
#define L_DEBUG   2
#define WARNING 3
#define ERROR   4
#define FATAL   5

#define LOG(level, msg) Log(#level, msg, __FILE__, __LINE__)

#define REF_SIZE 32
#define LOG_PATH "/home/zack/code_work/github_work/My_Cpp_Programming/HTTPServer/server/log/log1"

static std::string NowTime() {
    time_t t = time(nullptr);
    char ref[REF_SIZE];
    strftime(ref, REF_SIZE, "%Y-%m-%d %H:%M:%S", localtime(&t));
    return ref;
}

// [日志级别][时间戳][日志信息][错误文件名称][错误行数]
// 日志级别：INFO，WARNIG,ERROR,FATAL
// 时间戳：ctime->time
// 日志信息：__FILE__， __LINE__
void Log(const std::string& level, const std::string& msg, const std::string& file_name, int line) {
    std::string errno_msg;
    if (level != "INFO") {
        errno_msg += "[ "; errno_msg += level; errno_msg += " ]";
        errno_msg += "[ "; errno_msg += NowTime(); errno_msg += " ]";
        errno_msg += "[ "; errno_msg += msg; errno_msg += " ]";
        errno_msg += "[ "; errno_msg += file_name; errno_msg += " ]";
        errno_msg += "[ "; errno_msg += std::to_string(line); errno_msg += "rows ]";
    }else {
        //printf("[ %s ][ %s ][ %-30s]\n", level.c_str(), std::to_string(time(nullptr)).c_str(), msg.c_str());
        errno_msg += "[ "; errno_msg += level; errno_msg += " ]";
        errno_msg += "[ "; errno_msg += NowTime(); errno_msg += " ]";
        errno_msg += "[ "; errno_msg += msg; errno_msg += " ]";
    }
    std::cout << errno_msg << std::endl;
#if 0
    std::ofstream ofs;
    ofs.open(LOG_PATH, std::ios::out | std::ios::app | std::ios::trunc);
    if (ofs.is_open()) {
        ofs << errno_msg << std::endl;
    }else {
        printf("[ %s ][ %s ][ %s ][ %s ][ %drows ]\n", "WARNING", NowTime().c_str(), "Log ofstream error!", __FILE__, __LINE__);
        //exit(6);
    }
    ofs.close();
#endif
}



#endif //HTTPSERVER_LOG_HPP
