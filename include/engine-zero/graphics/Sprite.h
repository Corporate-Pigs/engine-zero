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
    Sprite(const Rectangle<int32_t>& subSpriteRect);
    virtual ~Sprite() = default;
    virtual void render(const Transform& transform) const = 0;

   protected:
    const std::unique_ptr<Rectangle<int32_t>> subspriteRectangle;

    friend class GraphicsEngine;
};

}  // namespace Engine
