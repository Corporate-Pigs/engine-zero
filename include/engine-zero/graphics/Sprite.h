#pragma once

#include <memory>

#include "engine-zero/graphics/Renderable.h"
#include "engine-zero/graphics/Transform.h"

namespace Engine {

/*
 * Represents an object capable of being rendered
 */
class Sprite : public Renderable {
   public:
    Sprite() = default;
    Sprite(const Rectangle& subSpriteRect);
    virtual ~Sprite() = default;
    virtual void render(const Transform* transform) const = 0;

   protected:
    const Rectangle mSubspriteRect;
};

}  // namespace Engine
