#include "engine-zero/physics/RigidBody.h"

#include <stdio.h>

Engine::RigidBody::RigidBody(Transform* transform, bool movable) : transform(transform), isStatic(!movable) {}

void Engine::RigidBody::moveHorizontal(const float speed) {
    if(isOnGround) {
        this->speed.x = speed;
    }
}

void Engine::RigidBody::moveVertical(const float speed) {
    if(isOnGround) {
        this->speed.y = speed;
    }
}

void Engine::RigidBody::stop() {
    if(isStatic) return;
    speed = {0, 0};
    acceleration = {0, 0};
}

bool Engine::RigidBody::isMovable() const {
    return !isStatic;
}

bool Engine::RigidBody::isIntersecting(const RigidBody& other) const {
    return transform->isIntersecting(*other.transform);
}

void Engine::RigidBody::applyGravity(const float magnitude) {
    if(isStatic) return;
    acceleration.y = magnitude;
}

void Engine::RigidBody::update(const double elapsedTime) {
    if(isStatic) return;

    float dt = static_cast<float>(elapsedTime);

    transform->mX += speed.x * dt + 0.5 * acceleration.x * dt * dt;
    transform->mY += speed.y * dt + 0.5 * acceleration.y * dt * dt;

    speed += acceleration * dt;
    printf("%f\n", speed.y);
}
