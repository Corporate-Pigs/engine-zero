#pragma once

#include <cstdint>

namespace Engine {

/*
 * Represents a screen color.
 */
class Color {
   public:
    Color();
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    static Color white();
    static Color black();
    uint8_t r, g, b, a;
};

}  // namespace Engine
