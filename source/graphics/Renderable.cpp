#include "engine-zero/graphics/Renderable.h"

Engine::Renderable::Renderable() : size(0.0f, 0.0f) {}

Engine::Renderable::Renderable(const cppvec::Vec2<float>& size) : size(size) {}

Engine::Renderable::~Renderable() {}

const cppvec::Vec2<float>& Engine::Renderable::getSize() const { return size; }

void Engine::Renderable::flipVertically(bool flip) {
    mFlipVertically = flip;
}
void Engine::Renderable::flipHorizontally(bool flip) {
    mFlipHorizontally = flip;
}

int Engine::Renderable::getAlpha() { return mAlpha; }

void Engine::Renderable::setAlpha(int alpha) { mAlpha = alpha; }