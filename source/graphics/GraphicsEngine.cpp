#include "engine-zero/graphics/GraphicsEngine.h"

#include "engine-zero/graphics/AnimatedSprite.h"
#include "engine-zero/resource/Tiled.h"

Engine::GraphicsEngine::GraphicsEngine(const Options* options)
    : windowSize(options->windowWidth, options->windowHeight),
      mCamera({0.0f, 0.0f, options->windowWidth * 0.5f, options->windowHeight * 0.5f}, { options->windowWidth, options->windowHeight } ) {
    for (int i = 0; i < GRAPHICS_ENGINE_RENDERING_LAYERS; i++) {
        mRenderingLayers[i].mIndex = i;
    }
}

Engine::AnimatedSprite* Engine::GraphicsEngine::createAnimatedSprite(const std::string sheetPath, uint32_t spriteId) {
    Engine::TiledTileSheet tiledTileSheet;
    Engine::TiledTileSheet::fromJson(sheetPath, tiledTileSheet);
    const auto& sheetTile = tiledTileSheet.tiles[spriteId];

    if (!sheetTile.keyframes.empty()) {
        auto animatedSprite = new AnimatedSprite();
        for (const auto& keyframe : sheetTile.keyframes) {
            auto sprite = std::shared_ptr<Sprite>(createSpriteFromSheet(sheetPath, keyframe.tileId));
            animatedSprite->addKeyframe({sprite, keyframe.duration});
        }
        mAnimatedSprites.push_back(std::unique_ptr<AnimatedSprite>(animatedSprite));
        return animatedSprite;
    }
    return nullptr;
};

Engine::Sprite* Engine::GraphicsEngine::createSpriteFromSheet(const std::string sheetPath, uint32_t spriteId) {
    Engine::TiledTileSheet tiledTileSheet;
    Engine::TiledTileSheet::fromJson(sheetPath, tiledTileSheet);
    const auto& sheetTile = tiledTileSheet.tiles[spriteId];

    Engine::Rectangle<int32_t> spriteRectangle;
    tiledTileSheet.computeRectangleForTileId(spriteId, spriteRectangle);
    auto sprite = createSprite(tiledTileSheet.image, spriteRectangle);
    
    for(const auto& object : sheetTile.objectGroup.objects) {
        if(object.type == "BoundingBox") {
            sprite->boundingRectangle.position.x = object.x;
            sprite->boundingRectangle.position.y = object.y;
            sprite->boundingRectangle.size.x = object.width;
            sprite->boundingRectangle.size.y = object.height;
        }
    }

    return sprite;
};

void Engine::GraphicsEngine::renderLayers() {
    // render and clear rendering layers
    
    Transform viewTransform = mCamera.getTransform();

    for (int i = 0; i < GRAPHICS_ENGINE_RENDERING_LAYERS; i++) {
        auto layerPtr = &mRenderingLayers[i];
        while (!layerPtr->mRenderingUnits.empty()) {
            auto ru = &layerPtr->mRenderingUnits.back();
            auto modelTransform = &ru->transform;
            Transform mvpTransform = *modelTransform * viewTransform;
            ru->renderable.render(mvpTransform);
            layerPtr->mRenderingUnits.pop_back();
        }
    }
}

void Engine::GraphicsEngine::updateAnimatedSprites(double elapsedTime) {
    for (auto& sprite : mAnimatedSprites) {
        sprite->update(elapsedTime);
    }
}

void Engine::GraphicsEngine::centerCameraOn(float x, float y) {
    mCamera.moveTo(x - mCamera.rectangle.size.x * 0.5f, y - mCamera.rectangle.size.y * 0.5f);
}

void Engine::GraphicsEngine::centerCameraOn(float x) {
    mCamera.moveTo(x - mCamera.rectangle.size.y * 0.5f, mCamera.rectangle.position.x);
}

void Engine::GraphicsEngine::flush() {
    for (int i = 0; i < GRAPHICS_ENGINE_RENDERING_LAYERS; i++) {
        auto layerPtr = &mRenderingLayers[i];
        layerPtr->mRenderingUnits.clear();
    }
    destroyCaches();
}

void Engine::GraphicsEngine::destroyCaches() {}