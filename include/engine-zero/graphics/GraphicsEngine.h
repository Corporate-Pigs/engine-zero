#pragma once

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "engine-zero/core/EngineOptions.h"
#include "engine-zero/graphics/AnimatedSprite.h"
#include "engine-zero/graphics/Camera.h"
#include "engine-zero/graphics/Sprite.h"
#include "engine-zero/graphics/Transform.h"

#define GRAPHICS_ENGINE_RENDERING_LAYERS 10

namespace Engine {

/*
 * Implements the Graphics rendering logic.
 */
class GraphicsEngine {
   public:
    GraphicsEngine(const Options* options);
    virtual ~GraphicsEngine() = default;

    virtual Renderable* createSprite(const std::string path, const Rectangle& subSpriteRectangle = {0, 0, 0, 0}) = 0;
    virtual void render(Renderable* sprite, const Transform* transform) = 0;
    Renderable* createAnimatedSprite(const std::string sheetPath, uint32_t spriteId);

    void centerCameraOn(float x, float y);
    void centerCameraOn(float x);

    // clear current engine context
    // (rendering units, caches...)
    void flush();

   protected:
    /*
     * Represents the basic necessary data
     * to render an unit to the screen (sprite, text, squares...)
     */
    struct RenderingUnit {
        const Renderable* renderable;
        const Transform* transform;
    };

    /*
     * Represents a rendering layer
     * Layers should be rendered in order of lower index to higher index
     */
    struct RenderingLayer {
        int mIndex;
        std::vector<RenderingUnit> mRenderingUnits;
        bool operator<(const RenderingLayer& other) const { return mIndex < other.mIndex; }
    };

    // TODO: investigate changing this into a set for more fine grain layers
    RenderingLayer mRenderingLayers[GRAPHICS_ENGINE_RENDERING_LAYERS];
    std::map<std::string, std::unique_ptr<Sprite>> mSpriteCache;
    std::vector<std::unique_ptr<AnimatedSprite>> mAnimatedSprites;
    Camera mCamera;
    float mWindowWidth, mWindowHeight;

    virtual void start() = 0;
    virtual void render(double elapsedTime) = 0;
    virtual void destroy() = 0;

    void renderLayers();
    void updateAnimatedSprites(double elapsedTime);
    void destroyCaches();

   private:
    void computeRenderingTransform(const Transform* objectTransform, Transform& renderingTransform, float xScale,
                                   float yScale);

    friend class CoreEngine;
};

}  // namespace Engine