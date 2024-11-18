#pragma once

#include <SDL.h>

#include "engine-zero/core/EngineOptions.h"
#include "engine-zero/graphics/GraphicsEngine.h"

namespace Engine {

class SDLGraphicsEngine : public Engine::GraphicsEngine {
   public:
    SDLGraphicsEngine(SDL_Window* window, Engine::Options* options);

    Sprite* createSprite(const std::string path) override;
    Sprite* createSprite(const std::string path, const Rectangle<int32_t>& subSpriteRectangle) override;
    void render(const Renderable& renderable, const Transform& transform) override;

    void start() override;
    void render(double elapsedTime) override;
    void destroy() override;

   private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    std::map<std::string, SDL_Texture*> mTextureCache;

    SDL_Texture* createSDLTexture(const std::string path);
};

}  // namespace Engine