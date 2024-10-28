#pragma once

#include "engine-zero/graphics/GraphicsEngine.h"
#include "engine-zero/ui/UserInterface.h"
#include "engine-zero/physics/PhysicsEngine.h"

namespace Engine {

/*
 * Represents the current runtime context of the engine.
 */
struct Context {
    GraphicsEngine* graphics;
    UserInterface* ui;
    PhysicsEngine* physics;
    double elapsedTime;
};

}  // namespace Engine