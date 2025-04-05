#include "engine-zero/core/Actor.h"

#include <cassert>

#include "engine-zero/tools/Logger.h"

Engine::Actor::Actor(uint32_t uid, const Transform& transform, const cppvec::Vec2<float>& offset) 
: uid(uid), transform(transform), mActive(true), anchorOffset(offset) {}

void Engine::Actor::start(Context* context) {
    onStart(context);
    for(const auto childPtr : children) {
        childPtr->start(context);
    }
}

void Engine::Actor::update(Context* context) {
    if (!mActive) return;
    onUpdate(context);
    for(const auto childPtr : children) {
        childPtr->update(context);
    }
}

void Engine::Actor::render(Context* context) {
    if (!mActive) return;
    onRender(context);
    for(const auto childPtr : children) {
        childPtr->render(context);
    }
}

void Engine::Actor::destroy(Context* context) {
    setActive(false);
    onDestroy(context);
}

void Engine::Actor::onStart(Context* context) {}
void Engine::Actor::onUpdate(Context* context) {}
void Engine::Actor::onRender(Context* context) {}
void Engine::Actor::onDestroy(Context* context) {}

void Engine::Actor::addChild(Engine::Actor* child) {
    assert(child);
    child->parent = this;
    children.push_back(child);
}

Engine::Actor* Engine::Actor::setActive(bool active) {
    mActive = active;
    return this;
}

bool Engine::Actor::isActive() {
    return mActive;
}

Engine::Actor* Engine::Actor::setOffset(const cppvec::Vec2<float>& offset) {
    anchorOffset = offset;
    return this;
}
