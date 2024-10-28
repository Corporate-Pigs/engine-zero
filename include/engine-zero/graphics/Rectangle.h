#pragma once

namespace Engine {

/*
 * Represents a position and size on the screen.
 */
class Rectangle {
   public:
    Rectangle() = default;
    Rectangle(float x, float y, float width, float height);
    float mX = 0.0f, mY = 0.0f, mWidth = 0.0f, mHeight = 0.0f;
    bool isDefault() const;
    bool isIntersecting(const Rectangle& other);
};

}  // namespace Engine