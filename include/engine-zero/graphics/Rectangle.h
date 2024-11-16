#pragma once

#include <cppvec/vec2.h>

namespace Engine {

/*
 * Represents a position and size on the screen.
 */
class Rectangle {
   public:
    Rectangle();
    Rectangle(float x, float y, float width, float height);
    cppvec::Vec2<float> position;
    cppvec::Vec2<float> size;
    bool isIntersecting(const Rectangle& other);
};

}  // namespace Engine