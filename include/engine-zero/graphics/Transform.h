#pragma once

#include <cstdint>

#include "engine-zero/graphics/Rectangle.h"

namespace Engine {

/*
 * Represents a position and size on the screen.
 */
class Transform {
   public:
    Transform() = default;
    Transform(const cppvec::Vec2<float>& position, uint16_t layer);
    Transform(const cppvec::Vec2<float>& position, const cppvec::Vec2<float>& scale, uint16_t layer);

    Transform operator*(const Transform& other) const;

    cppvec::Vec2<float> position = {0, 0};
    cppvec::Vec2<float> scale = {0, 0};
    float rotation = 0;
    uint16_t layer = 0;
};

}  // namespace Engine
