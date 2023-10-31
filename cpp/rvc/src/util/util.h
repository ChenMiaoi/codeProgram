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

#define INFO(msg) \
    do { \
        Logger("INFO", msg, __FILE__, __LINE__); \
    } while(0)
#define DEBUG(msg) \
    do { \
        Logger("DEBUG", msg, __FILE__, __LINE__); \
    } while(0)
#define WARN(msg) \
    do { \
        Logger("WARN", msg, __FILE__, __LINE__); \
    } while(0)
#define ERROR(msg) \
    do { \
        Logger("ERROR", msg, __FILE__, __LINE__); \
    } while(0)
#define FATAL(msg) \
    do { \
        Logger("FATAL", msg, __FILE__, __LINE__); \
    } while(0)

void Logger(const std::string& level, const std::string& msg, const std::string& file, int line);

#endif //! __UTIL_H__