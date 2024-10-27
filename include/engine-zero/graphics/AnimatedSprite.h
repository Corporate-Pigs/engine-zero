#pragma once

#include <memory>
#include <vector>

#include "engine-zero/core/Context.h"
#include "engine-zero/graphics/Renderable.h"
#include "engine-zero/graphics/Sprite.h"

namespace Engine {

class AnimatedSprite : public Renderable {
   public:
    struct Keyframe {
        Sprite* sprite;
        double durationInSeconds;
    };

    virtual void render(const Transform* transform) const;
    void addKeyframe(const Keyframe& keyframe);

   private:
    uint32_t mCurrentKeyframe;
    double mElapsedTimeInSecondsForCurrentSprite;
    std::vector<Keyframe> mKeyframes;
};

}  // namespace Engine
