#pragma once

#include <map>
#include <memory>
#include <vector>

#include "engine-zero/physics/MovingBody.h"
#include "engine-zero/physics/CollisionBox.h"

namespace Engine {

class PhysicsEngine {
   public:
    MovingBody* createMovingBody(Transform& transform);
    CollisionBox* createCollisionBox(const std::string& uid, const Transform& transform, const Rectangle<float> collisionBox);
    void update(const double elapsedTime);

   private:
    std::vector<std::unique_ptr<MovingBody>> movingBodies;
    std::vector<std::unique_ptr<CollisionBox>> collisionBoxes;
};

}  // namespace Engine
