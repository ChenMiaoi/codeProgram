#include "util.h"
#include <string>

// void Logger(const std::string &level, const std::string& func, const std::string &msg, const std::string &file, int line)  {
//     auto now = std::chrono::system_clock::now();
//     std::time_t time = std::chrono::system_clock::to_time_t(now);
//     auto time_format = std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");

//     std::ostringstream stream;
//     stream << time_format;

//     std::string time_str = stream.str();

//     int color = 0;
//     if (level == "INFO") {
//         color = 32;
//     } else if (level == "DEBUG") {
//         color = 34;
//     } else if (level == "WARN") {
//         color = 33;
//     } else {
//         color = 31;
//     }

//     printf("\033[0;%dm%s [%5s] <%s:%d> %s: %s\033[0m\n", color,  
//         time_str.c_str(), level.c_str(), file.substr(file.find_last_of("/") + 1).c_str(), line, func.c_str(), msg.c_str());    
// }

namespace rvc {
    
}