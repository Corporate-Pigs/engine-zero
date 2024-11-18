#pragma once

#include <memory>
#include <vector>

#include "engine-zero/graphics/Sprite.h"

namespace Engine {

class AnimatedSprite : public Renderable {
   public:
    struct Keyframe {
        std::shared_ptr<Sprite> sprite;
        double durationInSeconds;
    };
    virtual void render(const Transform& transform) const override;
    void addKeyframe(const Keyframe& keyframe);
    void update(double elapsedTime);
    void reset();
    bool isOver();
    void setLoop(bool loop);
    virtual void flipVertically(bool flip) override;
    virtual void flipHorizontally(bool flip) override;

   private:
    uint32_t mCurrentKeyframe = 0;
    double mElapsedTimeInSecondsForCurrentSprite = 0;
    std::vector<Keyframe> mKeyframes;
    bool loop = true;
    bool mIsOver = false;
};

}  // namespace Engine
