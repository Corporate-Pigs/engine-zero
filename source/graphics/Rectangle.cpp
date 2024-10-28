#include "engine-zero/graphics/Rectangle.h"

Engine::Rectangle::Rectangle(float x, float y, float width, float height)
    : mX(x), mY(y), mWidth(width), mHeight(height) {}

bool Engine::Rectangle::isDefault() const {
    return mHeight == 0.0f && mWidth == 0.0f && mX == 0.0f && mY == 0.0f;
}

bool Engine::Rectangle::isIntersecting(const Engine::Rectangle& other) {
    bool overlapX = (mX < other.mX + other.mWidth) && (mX + mWidth > other.mX);
    bool overlapY = (mY < other.mY + other.mHeight) && (mY + mHeight > other.mY);
    return overlapX && overlapY;
}
