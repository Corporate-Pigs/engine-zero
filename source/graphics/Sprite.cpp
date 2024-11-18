#include "engine-zero/graphics/Sprite.h"

Engine::Sprite::Sprite(cppvec::Vec2<float> size) : Renderable(size) {}

Engine::Sprite::Sprite(const Rectangle<int32_t>& subSpriteRect)
    : Renderable({static_cast<float>(subSpriteRect.size.x), static_cast<float>(subSpriteRect.size.y)}),
      subspriteRectangle(new Rectangle(subSpriteRect.position.x, subSpriteRect.position.y, subSpriteRect.size.x, subSpriteRect.size.y)) {}