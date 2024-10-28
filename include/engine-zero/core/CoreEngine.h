#pragma once

#include "engine-zero/core/EngineOptions.h"
#include "engine-zero/core/Game.h"
#include "engine-zero/graphics/GraphicsEngine.h"
#include "engine-zero/physics/PhysicsEngine.h"
#include "engine-zero/ui/UserInterface.h"

#define CORE_ENGINE_UPDATE_STEP 0.01f

namespace Engine {

/*
 * Implements the Game Engine core logic.
 */
class CoreEngine {
   private:
    Options mOptions;
    std::shared_ptr<Game> mGame;
    std::shared_ptr<GraphicsEngine> mGraphics;
    std::shared_ptr<UserInterface> mUI;
    std::shared_ptr<PhysicsEngine> mPhysics;

   public:
    CoreEngine(std::shared_ptr<UserInterface> ui, std::shared_ptr<Game> game, Options options);

    static Engine::CoreEngine* buildDefault(std::shared_ptr<Game> game, Engine::Options* options);

    void start();
};

}  // namespace Engine
