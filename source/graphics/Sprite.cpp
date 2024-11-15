#include "engine-zero/graphics/Sprite.h"

Engine::Sprite::Sprite(const Rectangle& subSpriteRect)
    : Renderable(subSpriteRect.mWidth, subSpriteRect.mHeight), mSubspriteRect(subSpriteRect) {}