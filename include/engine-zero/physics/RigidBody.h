#pragma once

#include <cppvec/vec2.h>

#include "engine-zero/graphics/Transform.h"

namespace Engine {
 
class RigidBody {
   public:
    RigidBody(Transform* transform, bool movable = true);
    uint32_t uid;
    void setSpeed(float xSpeed, float ySpeed);
    void stop();
    bool isIntersecting(const RigidBody& other) const;
    bool isMovable() const;
    void applyGravity(const float magnitude);
    void update(const double elapsedTime);
    Transform* transform;

   private:
    bool isStatic = false;
    float mass = 1.0f;
    cppvec::Vec2<float> speed = {0, 0};
    cppvec::Vec2<float> acceleration = {0, 0};
    
};

}  // namespace Engine
