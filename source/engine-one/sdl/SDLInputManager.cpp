#include <SDL.h>
#include <algorithm>

#include "engine-zero/sdl/SDLInputManager.h"
#include "engine-zero/tools/Logger.h"

Engine::InputKey getEngineKey(const SDL_Event& event) {
    SDL_KeyCode key = (SDL_KeyCode)event.key.keysym.sym;

    // Todo: Transform SDL_KeyCode into InputKey
    return (Engine::InputKey) key;
}

Engine::SDLInputManager::SDLInputManager() : InputManager(), inputMapping(), pressedKeys() { pressedKeys.reserve(5); }

void Engine::SDLInputManager::setActionMapping(const std::unordered_map<std::string, InputKey>& keyBinds) {
    inputMapping = keyBinds;
}

void Engine::SDLInputManager::setActionMapping(const std::string& action, const InputKey& key) { inputMapping[action] = key; }

bool Engine::SDLInputManager::removeFromActionMapping(const std::string& action) { return inputMapping.erase(action) > 0; }

bool Engine::SDLInputManager::isPerformingAction(const std::string& action) const {
    if (!inputMapping.contains(action)) return false;

    InputKey engineKey = inputMapping.at(action);

    return pressedKeys.contains(engineKey);
}

void Engine::SDLInputManager::update(const SDL_Event& event, const double& currentTime) {
    Engine::InputKey engineKey;

    switch (event.type) {
        case SDL_KEYDOWN:
            engineKey = getEngineKey(event);

            if (!pressedKeys.contains(engineKey)) {
                pressedKeys[engineKey] = currentTime;
            }

            break;
        case SDL_KEYUP:
            engineKey = getEngineKey(event);
            
            pressedKeys.erase(engineKey);
            break;
    }

    return;
}