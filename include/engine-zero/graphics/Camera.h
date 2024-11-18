#pragma once

#include <cstdint>

#include "engine-zero/graphics/Rectangle.h"
#include "engine-zero/graphics/Transform.h"

namespace Engine {

struct Camera {

    Rectangle<float> rectangle;
    const cppvec::Vec2<uint32_t> windowSize;

    Camera(const Rectangle<float>& initialPosition, const cppvec::Vec2<uint32_t>& windowSize);
    void moveTo(float x, float y);
    Transform getTransform();
};

}  // namespace Engine
