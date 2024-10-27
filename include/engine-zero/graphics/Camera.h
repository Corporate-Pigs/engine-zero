#pragma once

#include <cstdint>

#include "engine-zero/graphics/Rectangle.h"

namespace Engine {

struct Camera {
    Camera(const Rectangle& initialPosition);
    Rectangle rectangle;
    void moveTo(float x, float y);
};

}  // namespace Engine
