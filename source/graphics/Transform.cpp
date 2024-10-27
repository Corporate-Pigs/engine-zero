#include "engine-zero/graphics/Transform.h"

Engine::Transform::Transform(float x, float y, float width, float height, uint16_t layer, bool flipVertically = false,
                             bool flipHorizontally = false)
    : Rectangle(x, y, width, height),
      mLayer(layer),
      mFlipHorizontally(flipHorizontally),
      mFlipVertically(flipVertically) {}

Engine::Transform::Transform(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint16_t layer)
    : Engine::Transform(static_cast<float>(x), static_cast<float>(y), static_cast<float>(width),
                        static_cast<float>(height), layer) {}

bool Engine::Transform::containtsPoint(float x, float y) {
    float right = mX + mWidth;
    float bottom = mY + mHeight;
    return x >= this->mX && x <= right && y >= this->mY && y <= bottom;
}

void Engine::Transform::combineWith(const Rectangle& transform) {
    mX -= transform.mX;
    mY -= transform.mY;
}
