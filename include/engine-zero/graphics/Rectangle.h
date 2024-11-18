#pragma once

#include <cppvec/vec2.h>

namespace Engine {

/*
 * Represents a position and size on the screen.
 */
template <typename T>
class Rectangle {
   public:
    Rectangle() : position(0, 0), size(0, 0) {};
    Rectangle(T x, T y, T width, T height) : position(x, y), size(width, height) {};
    cppvec::Vec2<T> position;
    cppvec::Vec2<T> size;
    bool isIntersecting(const Engine::Rectangle<T>& other) {
        bool overlapX = (position.x < other.position.x + other.size.x) && (position.x + size.x > other.position.x);
        bool overlapY = (position.y < other.position.y + other.size.y) && (position.y + size.y > other.position.y);
        bool result = overlapX && overlapY;
        return result;
    }
};

}  // namespace EnginehorizontalOverlap