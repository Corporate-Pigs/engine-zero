#pragma once

#include <cppvec/vec2.h>

#include "engine-zero/graphics/Rectangle.h"
#include "engine-zero/graphics/Transform.h"

namespace Engine {

class RigidBody {
   public:
    RigidBody(Transform* bindedTransform, const Rectangle<float>& collisionBox, bool movable = true);
    void move(const cppvec::Vec2<float>& delta);
    void setHorizontalSpeed(float speed);
    void setVerticalSpeed(float speed);
    void setSpeed(const cppvec::Vec2<float>& speed);
    void setAcceleration(const cppvec::Vec2<float>& force);
    void stop();
    bool isIntersecting(const RigidBody& other);
    bool isMovable() const;
    void update(const double elapsedTime);
    bool hasCollision();

   private:
    uint32_t uid;
    bool isStatic = false;
    bool isColliding = false;
    float mass = 1.0f;
    Transform* bindedTransform;
    Rectangle<float> collisionBox;
    cppvec::Vec2<float> speed = {0, 0};
    cppvec::Vec2<float> acceleration = {0, 0};

    friend class PhysicsEngine;
};

}  // namespace Engine
