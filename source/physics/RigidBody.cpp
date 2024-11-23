#include "engine-zero/physics/RigidBody.h"

#include <stdio.h>

Engine::RigidBody::RigidBody(Transform* bindedTransform, const Rectangle<float>& collisionBox, bool movable)
    : bindedTransform(bindedTransform), collisionBox(collisionBox), isStatic(!movable) {
    if (bindedTransform != nullptr) {
        this->collisionBox.position += bindedTransform->position;
    }
}

void Engine::RigidBody::move(const cppvec::Vec2<float>& delta) {
    bindedTransform->position += delta;
    collisionBox.position += delta;
}

void Engine::RigidBody::setAcceleration(const cppvec::Vec2<float>& force) {
    if (isStatic) return;
    acceleration = force;
}

void Engine::RigidBody::setSpeed(const cppvec::Vec2<float>& speed) { this->speed = speed; }

void Engine::RigidBody::setHorizontalSpeed(float speed) { this->speed.x = speed; }

void Engine::RigidBody::setVerticalSpeed(float speed) { this->speed.y = speed; }

bool Engine::RigidBody::isMovable() const { return !isStatic; }

bool Engine::RigidBody::isIntersecting(const RigidBody& other) {
    return collisionBox.isIntersecting(other.collisionBox);
}

void Engine::RigidBody::update(const double elapsedTime) {
    if (isStatic) return;

    float dt = static_cast<float>(elapsedTime);
    auto auxiliarAcceleration = acceleration * dt * dt;
    speed += auxiliarAcceleration;
    auto positionDelta = (speed * dt) + auxiliarAcceleration;

    move(positionDelta);

    // printf("s: %f %f\n", speed.x, speed.y);
    // printf("%d - %f\n",isOnGround, transform->position.y);
}

bool Engine::RigidBody::hasCollision() { return isColliding; }

const cppvec::Vec2<float>& Engine::RigidBody::getSpeed() { return speed; }
