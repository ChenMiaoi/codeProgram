#ifndef __UTIL_H__
#define __UTIL_H__

#include <cstdio>
#include <iostream>
#include <chrono>
#include <ctime>
#include <locale>
#include <sstream>
#include <string>
#include <iomanip>

// #define INFO(msg) \
//     do { \
//         Logger("INFO", __func__, msg, __FILE__, __LINE__); \
//     } while(0)
// #define DEBUG(msg) \
//     do { \
//         Logger("DEBUG", __func__, msg, __FILE__, __LINE__); \
//     } while(0)
// #define WARN(msg) \
//     do { \
//         Logger("WARN", __func__, msg, __FILE__, __LINE__); \
//     } while(0)
// #define ERROR(msg) \
//     do { \
//         Logger("ERROR", __func__, msg, __FILE__, __LINE__); \
//     } while(0)
// #define FATAL(msg) \
//     do { \
//         Logger("FATAL", __func__, msg, __FILE__, __LINE__); \
//     } while(0)

namespace rvc {
    constexpr const char* RESET   = "\033[0m";
    constexpr const char* RED     = "\033[31m";
    constexpr const char* GREEN   = "\033[32m";
    constexpr const char* YELLOW  = "\033[33m";
    constexpr const char* BLUE    = "\033[34m";
    constexpr const char* MAGENTA = "\033[35m";
    constexpr const char* CYAN    = "\033[36m";
    constexpr const char* WHITE   = "\033[37m";

    enum class LogLevel {
        INFO,
        DEBUG,
        WARN,
        ERRON,
        FATAL,
    };

    template <LogLevel Level>
    static void Logger(const std::string& func, const std::string& file, int line, const std::string& msg) {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        auto time_format = std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");

        std::ostringstream stream;
        stream << time_format;

        std::string time_str = stream.str();

        std::string level;
        const char* color;
        switch (Level) {
            case LogLevel::INFO:
                level = "INFO";
                color = GREEN;
                break;
            case LogLevel::DEBUG:
                level = "DEBUG";
                color = BLUE;
                break;
            case LogLevel::WARN:
                level = "WARN";
                color = YELLOW;
                break;
            case LogLevel::ERRON:
                level = "ERROR";
                color = RED;
                break;
            case LogLevel::FATAL:
                level = "FATAL";
                color = RED;
                break;
            }

        std::cout << color 
                    << time_str
                    << "[ " << level << "] "
                    << "<" << file.substr(file.find_last_of("/") + 1) << ":" << line << "> "
                    << func << ": "
                    << msg
                    << RESET << std::endl;
        // printf("\033[%dm%s [%5s] <%s:%d> %s: %s\033[0m\n", color,  
        //     time_str.c_str(), level.c_str(), file.substr(file.find_last_of("/") + 1).c_str(), line, func.c_str(), msg.c_str());    
    }

    template <LogLevel Level>
    class Log {
    public:
        Log(int line, const char* func, const char* file)
            : _line(line), _func(func), _file(file)  {}
        ~Log() { Logger<Level>(_func, _file, _line, _oss.str()); }

        template <typename T>
        Log& operator<< (const T& msg) {
            _oss << msg;
            return *this;
        }
    private:
        int _line;
        std::string _func;
        std::string _file;
        std::ostringstream _oss;
    };
}

#define info    rvc::Log<rvc::LogLevel::INFO>   (__LINE__, __func__, __FILE__)
#define debug   rvc::Log<rvc::LogLevel::DEBUG>  (__LINE__, __func__, __FILE__)
#define warn    rvc::Log<rvc::LogLevel::WARN>   (__LINE__, __func__, __FILE__)
#define erron   rvc::Log<rvc::LogLevel::ERRON>  (__LINE__, __func__, __FILE__)
#define fatal   rvc::Log<rvc::LogLevel::FATAL>  (__LINE__, __func__, __FILE__)

// void Logger(const std::string& level, const std::string& func, const std::string& msg, const std::string& file, int line);

#endif //! __UTIL_H__
