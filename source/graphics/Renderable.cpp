#include "engine-zero/graphics/Renderable.h"

Engine::Renderable::Renderable(uint32_t width, uint32_t height) : width(width), height(height) {}

Engine::Renderable::~Renderable() {}

int Engine::Renderable::getAlpha() { return mAlpha; }

void Engine::Renderable::setAlpha(int alpha) { mAlpha = alpha; }