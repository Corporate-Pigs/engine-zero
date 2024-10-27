#pragma once

#include "engine-zero/graphics/Color.h"
#include "engine-zero/graphics/Transform.h"

namespace Engine {

/*
 * Represents an object capable of being rendered
 */
class Renderable {
   public:
    virtual ~Renderable();
    virtual void render(const Transform* transform) const = 0;
    int getAlpha();
    void setAlpha(int alpha);

   protected:
    uint8_t mAlpha;
};

}  // namespace Engine
