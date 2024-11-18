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

    virtual Sprite* createSprite(const std::string path) = 0;
    virtual Sprite* createSprite(const std::string path, const Rectangle<int32_t>& subSpriteRectangle) = 0;
    Sprite* createSpriteFromSheet(const std::string sheetPath, uint32_t spriteId);
    AnimatedSprite* createAnimatedSprite(const std::string sheetPath, uint32_t spriteId);
    virtual void render(const Renderable& renderable, const Transform& transform) = 0;

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
        const Renderable& renderable;
        const Transform transform;
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
    std::vector<std::unique_ptr<AnimatedSprite>> mAnimatedSprites;
    Camera mCamera;
    cppvec::Vec2<float> windowSize;

    virtual void start() = 0;
    virtual void render(double elapsedTime) = 0;
    virtual void destroy() = 0;

    void renderLayers();
    void updateAnimatedSprites(double elapsedTime);
    void destroyCaches();
    
    friend class CoreEngine;
};

}  // namespace Engine