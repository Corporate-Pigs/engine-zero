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
    Transform(float x, float y, float width, float height, uint16_t layer);
    void concatenate(const Transform& transform);
    uint16_t mLayer = 0;
    float mRotation = 0;
};

}  // namespace Engine
