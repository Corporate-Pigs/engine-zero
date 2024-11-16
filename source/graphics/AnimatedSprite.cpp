#include "engine-zero/graphics/AnimatedSprite.h"

void Engine::AnimatedSprite::render(const Engine::Transform& transform) const {
    if (mKeyframes.empty()) {
        return;
    }
    mKeyframes[mCurrentKeyframe].sprite->render(transform);
};

void Engine::AnimatedSprite::addKeyframe(const Keyframe& keyframe) {
    if (size.x == 0 || size.y == 0) {
        size = keyframe.sprite->getSize();
    }
    mKeyframes.push_back(keyframe);
};

void Engine::AnimatedSprite::update(double elapsedTime) {
    mElapsedTimeInSecondsForCurrentSprite += elapsedTime;
    auto currentKeyframeDuration = mKeyframes[mCurrentKeyframe].durationInSeconds;
    if (mElapsedTimeInSecondsForCurrentSprite >= currentKeyframeDuration) {
        mElapsedTimeInSecondsForCurrentSprite -= currentKeyframeDuration;
        mCurrentKeyframe = ++mCurrentKeyframe % mKeyframes.size();
        mKeyframes[mCurrentKeyframe].sprite->flipVertically(mFlipVertically);
        mKeyframes[mCurrentKeyframe].sprite->flipHorizontally(mFlipHorizontally);
    }
}

void Engine::AnimatedSprite::reset() {
    mElapsedTimeInSecondsForCurrentSprite = 0;
    mCurrentKeyframe = 0;
}

void Engine::AnimatedSprite::flipVertically(bool flip) {
    Renderable::flipVertically(flip);
    if (mKeyframes.empty()) {
        return;
    }
    mKeyframes[mCurrentKeyframe].sprite->flipVertically(mFlipVertically);
};

void Engine::AnimatedSprite::flipHorizontally(bool flip) {
    Renderable::flipHorizontally(flip);
    if (mKeyframes.empty()) {
        return;
    }
    mKeyframes[mCurrentKeyframe].sprite->flipHorizontally(mFlipHorizontally);
};