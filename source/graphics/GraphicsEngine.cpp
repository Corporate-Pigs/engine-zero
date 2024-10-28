#include "engine-zero/graphics/GraphicsEngine.h"

Engine::GraphicsEngine::GraphicsEngine(const Options* options)
    : mWindowWidth(options->windowWidth), 
    mWindowHeight(options->windowHeight), 
    mCamera({0.0f, 0.0f, static_cast<float>(options->windowWidth), static_cast<float>(options->windowHeight)}) {
    for (int i = 0; i < GRAPHICS_ENGINE_RENDERING_LAYERS; i++) {
        mRenderingLayers[i].mIndex = i;
    }
}

void Engine::GraphicsEngine::renderLayers() {
    // render and clear rendering layers
    Transform renderingTransform;
    double xScale = mWindowWidth / mCamera.rectangle.mWidth;
    double yScale = mWindowHeight / mCamera.rectangle.mHeight;

    for (int i = 0; i < GRAPHICS_ENGINE_RENDERING_LAYERS; i++) {
        auto layerPtr = &mRenderingLayers[i];
        while (!layerPtr->mRenderingUnits.empty()) {
            auto ru = &layerPtr->mRenderingUnits.back();
            if (ru->renderable != nullptr) {
                computeRenderingTransform(
                    ru->transform, 
                    renderingTransform,
                    xScale,
                    yScale);
                ru->renderable->render(&renderingTransform);
            }
            layerPtr->mRenderingUnits.pop_back();
        }
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

void Engine::GraphicsEngine::destroyCaches() {
    mSpriteCache.clear();
}

void Engine::GraphicsEngine::computeRenderingTransform(
    const Transform* objectTransform, 
    Transform& renderingTransform,
    float xScale, 
    float yScale) {

    renderingTransform = *objectTransform;

    renderingTransform.mX -= mCamera.rectangle.mX;
    renderingTransform.mY -= mCamera.rectangle.mY;

    renderingTransform.mX *= xScale;
    renderingTransform.mY *= yScale;
    renderingTransform.mWidth *= xScale;
    renderingTransform.mHeight *= yScale;
}