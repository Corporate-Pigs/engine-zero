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
    virtual void render(const Transform& transform) const = 0;
    int getAlpha();
    void setAlpha(int alpha);
    const cppvec::Vec2<float>& getSize() const;
    virtual void flipVertically(bool flip);
    virtual void flipHorizontally(bool flip);
    
   protected:
    uint8_t mAlpha;
    cppvec::Vec2<float> size;
    bool mFlipVertically = false, mFlipHorizontally = false;
};

}  // namespace Engine
