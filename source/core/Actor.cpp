#include "engine-zero/core/Actor.h"

#include "engine-zero/tools/Logger.h"

Engine::Actor::Actor(uint32_t uid, const Transform& transform) : uid(uid), transform(transform), mActive(true) {}

void Engine::Actor::start(Context* context) {
    if (!mActive) return;
    onStart(context);
}

void Engine::Actor::update(Context* context) {
    if (!mActive) return;
    onUpdate(context);
}

void Engine::Actor::render(Context* context) {
    if (!mActive) return;
    onRender(context);
}

void Engine::Actor::destroy(Context* context) {
    setActive(false);
    onDestroy(context);
}

void Engine::Actor::onStart(Context* context) {}
void Engine::Actor::onUpdate(Context* context) {}
void Engine::Actor::onRender(Context* context) {}
void Engine::Actor::onDestroy(Context* context) {}

Engine::Actor* Engine::Actor::setActive(bool active) {
    mActive = active;
    return this;
}
