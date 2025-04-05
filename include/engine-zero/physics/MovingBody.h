#pragma once

#include <cppvec/vec2.h>

#include "engine-zero/physics/CollisionBox.h"
#include "engine-zero/graphics/Transform.h"

namespace Engine {

class MovingBody {
   public:
    MovingBody(Transform& actorTransform);
    void move(const cppvec::Vec2<float>& delta);
    void setHorizontalSpeed(float speed);
    void setVerticalSpeed(float speed);
    void setSpeed(const cppvec::Vec2<float>& speed);
    void setAcceleration(const cppvec::Vec2<float>& force);
    void update(const double elapsedTime);

    const cppvec::Vec2<float>& getSpeed();

   private:
    uint32_t uid;
    float mass = 1.0f;
    Transform& actorTransform;
    cppvec::Vec2<float> speed = {0, 0};
    cppvec::Vec2<float> acceleration = {0, 0};

    friend class PhysicsEngine;
};

}  // namespace Engine
