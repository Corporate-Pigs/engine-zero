#include <SDL.h>

#include <string>

#include "engine-zero/graphics/Sprite.h"

namespace Engine {

class SDLSprite : public Sprite {
   public:
    SDLSprite(SDL_Texture* texture, SDL_Renderer* renderer, const Rectangle& subSpriteRect);
    virtual void render(const Transform& transform) const override;

   private:
    SDL_Texture* mTexture;
    SDL_Renderer* mRenderer;
};

}  // namespace Engine