#pragma once

#include "engine-zero/graphics/GraphicsEngine.h"
#include "engine-zero/ui/UserInterface.h"

namespace Engine {

/*
 * Represents the current runtime context of the engine.
 */
struct Context {
    Context(GraphicsEngine* graphics, UserInterface* ui);
    GraphicsEngine* graphics;
    UserInterface* ui;
    double elapsedTime;
};

}  // namespace Engine