#pragma once

#include "engine-zero/core/EngineOptions.h"
#include "engine-zero/graphics/GraphicsEngine.h"
#include "engine-zero/ui/UIState.h"
#include "engine-zero/ui/Input.h"

namespace Engine {

/*
 * Implements the User Interaction logic
 */
class UserInterface {
   public:
    UserInterface(Options* options);
    virtual GraphicsEngine* enableGraphics() = 0;
    virtual UIState* getState() = 0;

    virtual void exit() = 0;
    virtual bool isRunning() = 0;

    virtual void start() = 0;
    virtual void update() = 0;
    virtual void destroy() = 0;

    virtual double getTime() = 0;

    virtual InputManager* getInputManager() = 0;

   protected:
    bool mIsRunning;
    Options mOptions;
    UIState mState;
};
}  // namespace Engine
