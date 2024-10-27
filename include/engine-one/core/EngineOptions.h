#pragma once

#include <string>
#include <cinttypes>

namespace Engine {

/*
 * Holds the initial configuration values of the engine.
 */
class Options {
   public:
    Options(std::string windowTitle, int windowWidth, int windowHeight);
    uint16_t windowWidth, windowHeight;
    std::string windowTitle;
};
}  // namespace Engine