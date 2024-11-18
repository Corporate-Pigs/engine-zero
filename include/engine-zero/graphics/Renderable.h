#pragma once

#include <cppvec/vec2.h>

#include "engine-zero/graphics/Transform.h"

namespace Engine {

/*
 * Represents an object capable of being rendered
 */
class Renderable {
   public:
    Renderable();
    Renderable(const cppvec::Vec2<float>& size);
    virtual ~Renderable();
    int getAlpha();
    void setAlpha(uint8_t alpha);
    const cppvec::Vec2<float>& getSize() const;
    const Rectangle<float>& getBoundingRectangle() const;

    virtual void flipVertically(bool flip);
    virtual void flipHorizontally(bool flip);
    
    virtual void render(const Transform& transform) const = 0;

   protected:
    uint8_t mAlpha;
    cppvec::Vec2<float> size;
    Rectangle<float> boundingRectangle;
    bool mFlipVertically = false, mFlipHorizontally = false;
};

}  // namespace Engine
