#include "engine-zero/graphics/Sprite.h"

Engine::Sprite::Sprite(cppvec::Vec2<float> size) : Renderable(size) {}

Engine::Sprite::Sprite(const Rectangle& subSpriteRect) : Renderable(subSpriteRect.size),
      subspriteRectangle(new Rectangle(subSpriteRect.position.x, subSpriteRect.position.y, subSpriteRect.size.x,
                                       subSpriteRect.size.y)) {}