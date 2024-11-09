#include "engine-zero/graphics/AnimatedSprite.h"

void Engine::AnimatedSprite::render(const Engine::Transform* transform) const {
    if (mKeyframes.empty()) {
        return;
    }
    mKeyframes[mCurrentKeyframe].sprite->render(transform);
};

void Engine::AnimatedSprite::addKeyframe(const Keyframe& keyframe) { 
    mKeyframes.push_back(keyframe); 
};

void Engine::AnimatedSprite::update(double elapsedTime) {
    mElapsedTimeInSecondsForCurrentSprite += elapsedTime;
    auto currentKeyframeDuration = mKeyframes[mCurrentKeyframe].durationInSeconds;
    if (mElapsedTimeInSecondsForCurrentSprite >= currentKeyframeDuration) {
        mElapsedTimeInSecondsForCurrentSprite -= currentKeyframeDuration;
        mCurrentKeyframe = ++mCurrentKeyframe % mKeyframes.size();
    }
}