#include "engine-zero/physics/MovingBody.h"

#include <stdio.h>

Engine::MovingBody::MovingBody(Transform& bindedTransform) : actorTransform(bindedTransform) {}

void Engine::MovingBody::move(const cppvec::Vec2<float>& delta) { actorTransform.position += delta; }

void Engine::MovingBody::setAcceleration(const cppvec::Vec2<float>& force) { acceleration = force; }

void Engine::MovingBody::setSpeed(const cppvec::Vec2<float>& speed) { this->speed = speed; }

void Engine::MovingBody::setHorizontalSpeed(float speed) { this->speed.x = speed; }

void Engine::MovingBody::setVerticalSpeed(float speed) { this->speed.y = speed; }

void Engine::MovingBody::update(const double elapsedTime) {
    float dt = static_cast<float>(elapsedTime);
    auto auxiliarAcceleration = acceleration * dt * dt;
    speed += auxiliarAcceleration;
    auto positionDelta = (speed * dt) + auxiliarAcceleration;

    move(positionDelta);
}

const cppvec::Vec2<float>& Engine::MovingBody::getSpeed() { return speed; }
