#include "engine-zero/sdl/SDLUserInterface.h"

#include <cassert>
#include <memory>

#include "engine-zero/sdl/SDLGraphicsEngine.h"
#include "engine-zero/tools/Logger.h"
#include "engine-zero/ui/Input.h"

// Debug :: Remove
#include <iostream>
#include <sstream>

Engine::SDLUserInterface::SDLUserInterface(Engine::Options* options)
    : UserInterface(options), mWindow(nullptr), inputManager(new SDLInputManager()) {}

Engine::GraphicsEngine* Engine::SDLUserInterface::enableGraphics() {
    return new Engine::SDLGraphicsEngine(mWindow, &mOptions);
}

Engine::UIState* Engine::SDLUserInterface::getState() { return &mState; }

void Engine::SDLUserInterface::exit() { mIsRunning = false; }

bool Engine::SDLUserInterface::isRunning() { return mIsRunning; }

void Engine::SDLUserInterface::start() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::string sdlError = SDL_GetError();
        Logger::error("SDL could not initialize! SDL_Error: + " + sdlError + "\n");
        assert(false);
    }

    // Create window
    mWindow = SDL_CreateWindow(mOptions.windowTitle.c_str(),
                               // TODO: don't forget about these...
                               100 + 1080, 100, mOptions.windowWidth, mOptions.windowHeight, SDL_WINDOW_SHOWN);

    if (!mWindow) {
        std::string sdlError = SDL_GetError();
        Logger::error("Window could not be created! SDL_Error: + " + sdlError + "\n");
        assert(false);
    }

    // Todo: Debugging, remove
    /*enum Engine::InputKey key = K_w;
    std::unordered_map<std::string, InputKey> keyBinds;
    keyBinds["move_up"] = Engine::InputKey::K_w;
    keyBinds["move_left"] = Engine::InputKey::K_a;
    keyBinds["move_down"] = Engine::InputKey::K_s;
    keyBinds["move_right"] = Engine::InputKey::K_d;
    keyBinds["action"] = Engine::InputKey::K_f;

    inputManager->setActionMapping(keyBinds);*/

    mIsRunning = true;
}

void Engine::SDLUserInterface::update() {
    // Logger::verbose("=== Start of tick ===");

    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        std::stringstream ss;
        const double currentTime = getTime();

        switch (e.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                ss << std::hex << e.type;

                /*Logger::verbose("Event Type 0x" + ss.str() + " / " + std::to_string(e.key.type) +
                                " || SC: " + std::to_string(e.key.keysym.scancode) + " KC: " +
                   char(e.key.keysym.sym));*/

                inputManager->update(e, currentTime);

                break;
            default:
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        break;
                }
                break;
        }
    }

    // Todo: Debug, remove
    /*std::string actions[5] = {"move_up", "move_down", "move_left", "move_right", "action"};

    for (std::string action : actions) {
        if (inputManager->isPerformingAction(action)) {
            Logger::verbose("Performing action '" + action + "'");
        }
    }*/

    // Logger::verbose("=== End of tick ===");
}

void Engine::SDLUserInterface::destroy() {
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

double Engine::SDLUserInterface::getTime() {
    Uint32 ticks = SDL_GetTicks();
    return ticks / 1000.0;
}

Engine::InputManager* Engine::SDLUserInterface::getInputManager() { return inputManager.get(); }
