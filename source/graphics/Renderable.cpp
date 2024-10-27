#include "engine-zero/graphics/Renderable.h"

Engine::Renderable::~Renderable() {}

int Engine::Renderable::getAlpha() { return mAlpha; }

void Engine::Renderable::setAlpha(int alpha) { mAlpha = alpha; }