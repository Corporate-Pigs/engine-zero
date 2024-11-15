#include "engine-zero/graphics/GraphicsEngine.h"

#include "engine-zero/graphics/AnimatedSprite.h"
#include "engine-zero/resource/Tiled.h"

Engine::GraphicsEngine::GraphicsEngine(const Options* options)
    : mWindowWidth(options->windowWidth),
      mWindowHeight(options->windowHeight),
      mCamera({options->windowWidth * 0.25f, options->windowHeight * 0.25f,
               static_cast<float>(options->windowWidth * 0.5f), static_cast<float>(options->windowHeight * 0.5f)}) {
    for (int i = 0; i < GRAPHICS_ENGINE_RENDERING_LAYERS; i++) {
        mRenderingLayers[i].mIndex = i;
    }
}

Engine::Renderable* Engine::GraphicsEngine::createAnimatedSprite(const std::string sheetPath, uint32_t spriteId) {
    Engine::TiledTileSheet tiledTileSheet;
    Engine::TiledTileSheet::fromJson(sheetPath, tiledTileSheet);
    const auto& sheetTile = tiledTileSheet.tiles[spriteId];

    Engine::Rectangle spriteRectangle;
    if (!sheetTile.keyframes.empty()) {
        auto animatedSprite = new AnimatedSprite();
        for (const auto& keyframe : sheetTile.keyframes) {
            tiledTileSheet.computeRectangleForTileId(keyframe.tileId, spriteRectangle);
            animatedSprite->addKeyframe({createSprite(tiledTileSheet.image, spriteRectangle), keyframe.duration});
        }
        mAnimatedSprites.push_back(std::unique_ptr<AnimatedSprite>(animatedSprite));
        animatedSprite->width = spriteRectangle.mWidth;
        animatedSprite->height = spriteRectangle.mHeight;
        return animatedSprite;
    }
    return nullptr;
};

void Engine::GraphicsEngine::renderLayers() {
    // render and clear rendering layers
    Transform renderingTransform;
    double xScale = mWindowWidth / mCamera.rectangle.mWidth;
    double yScale = mWindowHeight / mCamera.rectangle.mHeight;

    for (int i = 0; i < GRAPHICS_ENGINE_RENDERING_LAYERS; i++) {
        auto layerPtr = &mRenderingLayers[i];
        while (!layerPtr->mRenderingUnits.empty()) {
            auto ru = &layerPtr->mRenderingUnits.back();
            computeRenderingTransform(ru->transform, renderingTransform, xScale, yScale);
            ru->renderable->render(&renderingTransform);
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
    mCamera.moveTo(x - mCamera.rectangle.mWidth * 0.5f, y - mCamera.rectangle.mHeight * 0.5f);
}

void Engine::GraphicsEngine::centerCameraOn(float x) {
    mCamera.moveTo(x - mCamera.rectangle.mWidth * 0.5f, mCamera.rectangle.mY);
}

void Engine::GraphicsEngine::flush() {
    for (int i = 0; i < GRAPHICS_ENGINE_RENDERING_LAYERS; i++) {
        auto layerPtr = &mRenderingLayers[i];
        layerPtr->mRenderingUnits.clear();
    }
    destroyCaches();
}

void Engine::GraphicsEngine::destroyCaches() { mSpriteCache.clear(); }

void Engine::GraphicsEngine::computeRenderingTransform(const Transform* objectTransform, Transform& renderingTransform,
                                                       float xScale, float yScale) {
    renderingTransform = *objectTransform;

    renderingTransform.mX -= mCamera.rectangle.mX;
    renderingTransform.mY -= mCamera.rectangle.mY;

    renderingTransform.mX *= xScale;
    renderingTransform.mY *= yScale;
    renderingTransform.mWidth *= xScale;
    renderingTransform.mHeight *= yScale;
}