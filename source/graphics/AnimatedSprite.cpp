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
        boundingRectangle = keyframe.sprite->getBoundingRectangle();
    }
    mKeyframes.push_back(keyframe);
};

void Engine::AnimatedSprite::update(double elapsedTime) {
    if(mIsOver) {
        return;
    }
    mElapsedTimeInSecondsForCurrentSprite += elapsedTime;
    auto currentKeyframeDuration = mKeyframes[mCurrentKeyframe].durationInSeconds;
    if (mElapsedTimeInSecondsForCurrentSprite >= currentKeyframeDuration) {
        if(mCurrentKeyframe == (mKeyframes.size() - 1) && !loop) {
            mIsOver = true;
            return;
        }
        mElapsedTimeInSecondsForCurrentSprite -= currentKeyframeDuration;
        mCurrentKeyframe = ++mCurrentKeyframe % mKeyframes.size();
        boundingRectangle = mKeyframes[mCurrentKeyframe].sprite->getBoundingRectangle();
    }
}

bool Engine::AnimatedSprite::isOver() {
    return mIsOver;
}

void Engine::AnimatedSprite::setLoop(bool loop) {
    this->loop = loop;
}

void Engine::AnimatedSprite::reset() {
    mElapsedTimeInSecondsForCurrentSprite = 0;
    mCurrentKeyframe = 0;
    mIsOver = false;
}

void Engine::AnimatedSprite::flipVertically(bool flip) {
    Renderable::flipVertically(flip);
    for(const auto& keyframe : mKeyframes) {
        keyframe.sprite->flipVertically(flip);
    }
};

void Engine::AnimatedSprite::flipHorizontally(bool flip) {
    Renderable::flipHorizontally(flip);
    for(const auto& keyframe : mKeyframes) {
        keyframe.sprite->flipHorizontally(flip);
    }
};