#pragma once

#include <SDL.h>

#include "engine-zero/core/EngineOptions.h"
#include "engine-zero/graphics/GraphicsEngine.h"

namespace Engine {

class SDLGraphicsEngine : public Engine::GraphicsEngine {
   public:
    SDLGraphicsEngine(SDL_Window* window, Engine::Options* options);

    virtual Sprite* createSprite(const std::string path, const Rectangle& subSpriteRectangle);
    virtual void render(Renderable* sprite, const Transform* transform);

    virtual void start();
    virtual void render();
    virtual void destroy();

   private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    std::map<std::string, SDL_Texture*> mTextureCache;

    SDL_Texture* createSDLTexture(const std::string path);
};

}  // namespace Engine