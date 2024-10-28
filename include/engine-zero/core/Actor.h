#pragma once

#include <vector>

#include "engine-zero/core/Context.h"
#include "engine-zero/graphics/Transform.h"

namespace Engine {

/*
 * Represents an actor part of a scene.
 */
class Actor {
   public:
    Actor(uint32_t uid, const Transform& transform);
    virtual ~Actor() = default;
    void start(Context* context);
    void update(Context* context);
    void render(Context* context);
    void destroy(Context* context);

    virtual void onStart(Context* context);
    virtual void onRender(Context* context);
    virtual void onUpdate(Context* context);
    virtual void onDestroy(Context* context);

    Actor* setActive(bool active);
    Transform transform;

   protected:
    uint32_t uid;
    bool mActive = true;
};

}  // namespace Engine
