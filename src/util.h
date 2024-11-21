//
// Created by kgil2 on 8/30/2024.
//

#ifndef GLFW2_UTIL_H
#define GLFW2_UTIL_H

#include <string>
#include <iostream>
#include <memory>
#include <functional>

#define Uptr std::unique_ptr
#define Sptr std::shared_ptr

namespace util {
    enum LogLevel {
        INFO,
        WARNING,
        EXCEPTION,
        ERROR
    };

    void printl(const std::string &string);
    void log(util::LogLevel level, const std::string &string);
}


#endif //GLFW2_UTIL_H
