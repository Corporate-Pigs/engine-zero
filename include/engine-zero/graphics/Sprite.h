#pragma once

#include <cppvec/vec2.h>

#include <memory>

#include "engine-zero/graphics/Renderable.h"
#include "engine-zero/graphics/Transform.h"

namespace Engine {

/*
 * Represents an object capable of being rendered
 */
class Sprite : public Renderable {
   public:
    Sprite(cppvec::Vec2<float> size);
    Sprite(const Rectangle& subSpriteRect);
    virtual ~Sprite() = default;
    virtual void render(const Transform& transform) const = 0;

   protected:
    const std::unique_ptr<Rectangle> subspriteRectangle;
};

}  // namespace Engine
