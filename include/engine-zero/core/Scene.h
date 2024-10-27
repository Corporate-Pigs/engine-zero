#pragma once

#include <vector>

#include "engine-zero/core/Actor.h"
#include "engine-zero/core/Context.h"
#include "engine-zero/core/SceneResult.h"

namespace Engine {

/*
 * Represents a game scene (screen on the game).
 */
class Scene {
   public:
    virtual ~Scene();
    void start(Context* context, SceneResult* result);
    void update(Context* context);
    void render(Context* context);
    void destroy(Context* context);
    SceneResult getResult();

    virtual int getId() = 0;
    virtual void onStart(Context* context) {};
    virtual void onRender(Context* context) {};
    virtual void onUpdate(Context* context) {};
    virtual void onDestroy(Context* context) {};
    virtual bool didFinish() = 0;

   protected:
    SceneResult mResult;
    void attachActor(Actor* object);

   private:
    std::vector<Actor*> mActors;
};

}  // namespace Engine