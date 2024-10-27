#include "engine-zero/graphics/Color.h"

Engine::Color::Color() : r(0), g(0), b(0), a(255) {}

Engine::Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

Engine::Color Engine::Color::white() { return Color(255, 255, 255, 255); }

Engine::Color Engine::Color::black() { return Color(0, 0, 0, 255); }
