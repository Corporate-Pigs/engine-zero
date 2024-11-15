#pragma once

#include <memory>
#include <vector>

#include "engine-zero/graphics/Renderable.h"

namespace Engine {

class AnimatedSprite : public Renderable {
   public:
    struct Keyframe {
        Renderable* sprite;
        double durationInSeconds;
    };

    virtual void render(const Transform* transform) const;
    void addKeyframe(const Keyframe& keyframe);
    void update(double elapsedTime);
    void reset();

   private:
    uint32_t mCurrentKeyframe = 0;
    double mElapsedTimeInSecondsForCurrentSprite = 0;
    std::vector<Keyframe> mKeyframes;
};

}  // namespace Engine
