#include "engine-zero/sdl/SDLSprite.h"

#include <SDL_image.h>

#include <cassert>

#include "engine-zero/sdl/SDLUtils.h"
#include "engine-zero/tools/Logger.h"

Engine::SDLSprite::SDLSprite(SDL_Texture* texture, SDL_Renderer* renderer, const Rectangle<int32_t>& subSpriteRect)
: Sprite(subSpriteRect), mRenderer(renderer), mTexture(texture) {}

void Engine::SDLSprite::render(const Transform& transform) const {
    SDL_FRect screenRectangle = {0.0f, 0.0f, size.x, size.y};
    transformToSDLFRect(transform, screenRectangle);

    auto flipHorizontally = mFlipHorizontally ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    auto flipVertically = mFlipVertically ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
    SDL_RendererFlip flipFlag = (SDL_RendererFlip)(flipHorizontally | flipVertically);

    if (subspriteRectangle == nullptr) {
        SDL_RenderCopyExF(mRenderer, mTexture, NULL, &screenRectangle, transform.rotation, nullptr, flipFlag);
        return;
    }

    SDL_Rect atlasRectangle;
    rectangleToSDLRect(*subspriteRectangle, atlasRectangle);
    SDL_RenderCopyExF(mRenderer, mTexture, &atlasRectangle, &screenRectangle, transform.rotation, nullptr, flipFlag);
}
