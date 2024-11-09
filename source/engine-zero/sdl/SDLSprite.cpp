#include "engine-zero/sdl/SDLSprite.h"

#include <SDL_image.h>

#include <cassert>

#include "engine-zero/sdl/SDLUtils.h"
#include "engine-zero/tools/Logger.h"

Engine::SDLSprite::SDLSprite(SDL_Texture* texture, SDL_Renderer* renderer, const Rectangle& subSpriteRect)
: Sprite(subSpriteRect), mRenderer(renderer), mTexture(texture) {}

void Engine::SDLSprite::render(const Transform* transform) const {
    SDL_FRect screenRectangle;
    rectangleToSDLFRect(transform, &screenRectangle);

    auto flipHorizontally = transform->mFlipHorizontally ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    auto flipVertically = transform->mFlipVertically ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
    SDL_RendererFlip flipFlag = (SDL_RendererFlip)(flipHorizontally | flipVertically);

    if (mSubspriteRect.isDefault()) {
        SDL_RenderCopyExF(mRenderer, mTexture, NULL, &screenRectangle, transform->mRotation, nullptr, flipFlag);
        return;
    }

    SDL_Rect atlasRectangle;
    rectangleToSDLRect(&mSubspriteRect, &atlasRectangle);
    SDL_RenderCopyExF(mRenderer, mTexture, &atlasRectangle, &screenRectangle, transform->mRotation, nullptr, flipFlag);
}
