#pragma once

#include "engine-zero/core/Context.h"
#include "engine-zero/core/Scene.h"
#include "engine-zero/core/SceneResult.h"

namespace Engine {

/*
 * Implements the Game logic. Handling scenes and their results is one of its uses.
 */
class Game {
   protected:
    std::unique_ptr<Scene> mActiveScene;
    std::map<int, Scene*> mScenesById;

   public:
    virtual ~Game();
    void start(Context* context);
    void update(Context* context);
    void render(Context* context);
    void destroy(Context* context);

    virtual void onStart(Context* context) = 0;
    virtual void onUpdate(Context* context) = 0;
    virtual Scene* getSceneFromResult(SceneResult* result) = 0;
};

}  // namespace Engine
