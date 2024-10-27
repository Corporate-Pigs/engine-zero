#pragma once

#include <iostream>
#include <string>

namespace Engine {

/*
 * Responsible for logging information
 */
class Logger {
   public:
    static void debug(std::string message) { std::cout << "[debug] " << message << std::endl; }
    static void error(std::string message) { std::cout << "[error] " << message << std::endl; }
    static void verbose(std::string message) { std::cout << "[verbose] " << message << std::endl; }
};

}  // namespace Engine