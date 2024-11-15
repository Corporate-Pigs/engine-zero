#pragma once

#include "engine-zero/graphics/Color.h"
#include "engine-zero/graphics/Transform.h"

namespace Engine {

/*
 * Represents an object capable of being rendered
 */
class Renderable {
   public:
    Renderable() = default;
    Renderable(uint32_t width, uint32_t height);
    virtual ~Renderable();
    virtual void render(const Transform* transform) const = 0;
    int getAlpha();
    void setAlpha(int alpha);
    uint32_t width, height;

   protected:
    uint8_t mAlpha;
};

}  // namespace Engine
