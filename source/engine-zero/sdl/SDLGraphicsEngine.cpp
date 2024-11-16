#include "engine-zero/sdl/SDLGraphicsEngine.h"

#include <SDL_image.h>

#include <cassert>

#include "engine-zero/resource/ResourceManager.h"
#include "engine-zero/sdl/SDLSprite.h"
#include "engine-zero/tools/Logger.h"

Engine::SDLGraphicsEngine::SDLGraphicsEngine(SDL_Window* window, Engine::Options* options)
    : Engine::GraphicsEngine(options), mWindow(window) {}

Engine::Sprite* Engine::SDLGraphicsEngine::createSprite(const std::string path, const Rectangle* subSpriteRectangle) {

    if (mTextureCache.count(path) == 0) {
        auto texture = createSDLTexture(path);
        mTextureCache[path] = texture;
    }

    auto texture = mTextureCache[path];

    Rectangle auxiliarRectangle;
    if(subSpriteRectangle == nullptr) {
        int32_t w, h;
        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        auxiliarRectangle.position = { 0.0f, 0.0f };
        auxiliarRectangle.size = { static_cast<float>(w), static_cast<float>(h) };
    }
    else {
        auxiliarRectangle = *subSpriteRectangle;
    }

    auto sprite = new SDLSprite(texture, mRenderer, auxiliarRectangle);
    return sprite;
}

void Engine::SDLGraphicsEngine::render(const Renderable& renderable, const Transform& transform) {
    auto layer = &mRenderingLayers[transform.mLayer];
    RenderingUnit ro = {renderable, { transform.position.x, transform.position.y, renderable.getSize().x, renderable.getSize().y, transform.mLayer}};
    layer->mRenderingUnits.push_back(ro);
}

void Engine::SDLGraphicsEngine::start() {
    // Create renderer for window
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == NULL) {
        std::string error = SDL_GetError();
        Logger::error("Renderer could not be created! SDL Error: " + error);
        assert(false);
    }

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::string error = IMG_GetError();
        Logger::error("SDL_image could not initialize! SDL_image Error: " + error);
        assert(false);
    }
}

void Engine::SDLGraphicsEngine::render(double elapsedTime) {
    SDL_SetRenderDrawColor(mRenderer, 0x55, 0x55, 0x55, 0xFF);
    SDL_RenderClear(mRenderer);

    updateAnimatedSprites(elapsedTime);
    renderLayers();

    SDL_RenderPresent(mRenderer);
}

SDL_Texture* Engine::SDLGraphicsEngine::createSDLTexture(const std::string path) {
    SDL_Surface* loadedImage = IMG_Load(ResourceManager::getPathForGraphicsResource(path).c_str());
    if (!loadedImage) {
        // TODO: I need to check these return values...
        std::string error = IMG_GetError();
        Logger::error("Unable to load image! " + path + " SDL_image Error : " + error);
        assert(false);
    }

    // Create texture from surface pixels
    SDL_Texture* mTexture = SDL_CreateTextureFromSurface(mRenderer, loadedImage);
    if (!mTexture) {
        // TODO: I need to check these return values...
        std::string error = SDL_GetError();
        Logger::error("Unable to create texture from " + path + " SDL Error: " + error);
        assert(false);
    }
    SDL_FreeSurface(loadedImage);
    return mTexture;
}

void Engine::SDLGraphicsEngine::destroy() {
    for (auto const& [key, mTexturePtr] : mTextureCache) {
        SDL_DestroyTexture(mTexturePtr);
    }
    this->destroyCaches();
    SDL_DestroyRenderer(mRenderer);
    IMG_Quit();
}