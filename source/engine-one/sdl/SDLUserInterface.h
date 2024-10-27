#include <SDL.h>

#include "engine-zero/ui/UserInterface.h"
#include "engine-zero/graphics/GraphicsEngine.h"
#include "SDLInputManager.h"

namespace Engine {

class SDLUserInterface : public Engine::UserInterface {
   public:
    SDLUserInterface(Engine::Options* options);
    virtual Engine::GraphicsEngine* enableGraphics() override;
    virtual UIState* getState() override;

    virtual void exit() override;
    virtual bool isRunning() override;

    virtual void start() override;
    virtual void update() override;
    virtual void destroy() override;

    virtual double getTime() override;

    virtual InputManager* getInputManager() override;

   private:
    SDL_Window* mWindow;
    std::unique_ptr<SDLInputManager> inputManager;
};
}  // namespace Engine