#pragma once

#include <map>
#include <memory>
#include <vector>

#include "engine-zero/physics/Collision.h"
#include "engine-zero/physics/RigidBody.h"

namespace Engine {

class PhysicsEngine {
   public:
    RigidBody* createRigidBody(Transform* transform, const Rectangle<float> collisionBox, bool isMovable = true);
    void update(const double elapsedTime);

   private:
    void solveCollision(RigidBody* bodyA, RigidBody* bodyB) const;
    std::vector<std::unique_ptr<RigidBody>> rigidBodies;
};

}  // namespace Engine
