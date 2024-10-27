#pragma once

#include <cstdint>

#include "engine-zero/graphics/Rectangle.h"

namespace Engine {

/*
 * Represents a position and size on the screen.
 */
class Transform : public Rectangle {
   public:
    Transform() = default;
    Transform(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint16_t layer);
    Transform(float x, float y, float width, float height, uint16_t layer, bool flipVertically, bool flipHorizontally);
    void combineWith(const Rectangle& transform);
    uint16_t mLayer = 0;
    float mRotation = 0;
    bool mFlipVertically = false, mFlipHorizontally = false;
    bool containtsPoint(float x, float y);
};

}  // namespace Engine
