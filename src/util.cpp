//
// Created by kgil2 on 9/2/2024.
//

#include "util.h"

void util::printl(const std::string &string) {
    std::cout << string << std::endl;
}

void util::log(util::LogLevel level, const std::string &string) {
    std::string levelString;
    switch (level) {
        case util::INFO:
            levelString = "[INFO]";
            break;
        case util::WARNING:
            levelString = "[WARNING]";
            break;
        case util::EXCEPTION:
            levelString = "[!! EXCEPTION !!]";
            break;
        case util::ERROR:
            levelString = "[!! ERROR !!]";
    }
    std::cout << levelString << " : " << string << std::endl;
}
