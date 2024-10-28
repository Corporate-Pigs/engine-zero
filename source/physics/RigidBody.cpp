#include "engine-zero/physics/RigidBody.h"

Engine::RigidBody::RigidBody(Transform* transform, bool movable) : transform(transform), isStatic(!movable) {}

void Engine::RigidBody::setSpeed(float xSpeed, float ySpeed) {
    speed.x = xSpeed;
    speed.y = ySpeed;
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
    speed += acceleration;
    transform->mX += speed.x * static_cast<float>(elapsedTime);
    transform->mY += speed.y * static_cast<float>(elapsedTime);
}
