#include "engine-zero/graphics/GraphicsEngine.h"

#include "engine-zero/graphics/AnimatedSprite.h"
#include "engine-zero/resource/Tiled.h"

Engine::GraphicsEngine::GraphicsEngine(const Options* options)
    : windowSize(options->windowWidth, options->windowHeight),
      mCamera({options->windowWidth * 0.25f, options->windowHeight * 0.25f,
               static_cast<float>(options->windowWidth * 0.5f), static_cast<float>(options->windowHeight * 0.5f)}) {
    for (int i = 0; i < GRAPHICS_ENGINE_RENDERING_LAYERS; i++) {
        mRenderingLayers[i].mIndex = i;
    }
}

Engine::AnimatedSprite* Engine::GraphicsEngine::createAnimatedSprite(const std::string sheetPath, uint32_t spriteId) {
    Engine::TiledTileSheet tiledTileSheet;
    Engine::TiledTileSheet::fromJson(sheetPath, tiledTileSheet);
    const auto& sheetTile = tiledTileSheet.tiles[spriteId];

    Engine::Rectangle spriteRectangle;
    if (!sheetTile.keyframes.empty()) {
        auto animatedSprite = new AnimatedSprite();
        for (const auto& keyframe : sheetTile.keyframes) {
            tiledTileSheet.computeRectangleForTileId(keyframe.tileId, spriteRectangle);
            auto sprite = std::shared_ptr<Sprite>(createSprite(tiledTileSheet.image, &spriteRectangle));

            animatedSprite->addKeyframe({sprite, keyframe.duration});
        }
        mAnimatedSprites.push_back(std::unique_ptr<AnimatedSprite>(animatedSprite));
        return animatedSprite;
    }
    return nullptr;
};

void Engine::GraphicsEngine::renderLayers() {
    // render and clear rendering layers
    Transform renderingTransform;
    auto scale = windowSize / mCamera.rectangle.size;

    for (int i = 0; i < GRAPHICS_ENGINE_RENDERING_LAYERS; i++) {
        auto layerPtr = &mRenderingLayers[i];
        while (!layerPtr->mRenderingUnits.empty()) {
            auto ru = &layerPtr->mRenderingUnits.back();
            computeRenderingTransform(&ru->transform, renderingTransform, scale);
            ru->renderable.render(renderingTransform);
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

void Engine::GraphicsEngine::computeRenderingTransform(const Transform* objectTransform, Transform& renderingTransform, const cppvec::Vec2<float>& scale) {
    renderingTransform = *objectTransform;

    renderingTransform.position -= mCamera.rectangle.position;
    renderingTransform.position *= scale;
    renderingTransform.size *= scale;
}