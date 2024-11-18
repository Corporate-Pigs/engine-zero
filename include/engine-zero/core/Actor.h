#pragma once

#include <cppvec/vec2.h>

#include <vector>

#include "engine-zero/core/Context.h"
#include "engine-zero/graphics/Transform.h"

namespace Engine {

/*
 * Represents an actor part of a scene.
 */
class Actor {
   public:
    Actor(uint32_t uid, const Transform& transform, const cppvec::Vec2<float>& offset = {0.0f, 0.0f});
    virtual ~Actor() = default;

    virtual void onStart(Context* context);
    virtual void onRender(Context* context);
    virtual void onUpdate(Context* context);
    virtual void onDestroy(Context* context);
    void addChild(Actor* child);

    Actor* setActive(bool active);
    bool isActive();
    Actor* setOffset(const cppvec::Vec2<float>& offset);
    Transform transform;

   protected:
    void start(Context* context);
    void update(Context* context);
    void render(Context* context);
    void destroy(Context* context);

    uint32_t uid;
    bool mActive = true;
    Actor* parent = nullptr;
    std::vector<Actor*> children;
    cppvec::Vec2<float> anchorOffset;

    friend class Scene;
};

}  // namespace Engine
