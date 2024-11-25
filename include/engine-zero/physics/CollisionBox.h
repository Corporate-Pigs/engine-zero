#pragma once

#include <set>
#include <string>

#include "engine-zero/graphics/Rectangle.h"
#include "engine-zero/graphics/Transform.h"

namespace Engine {

struct CollisionBox {
   public:
    CollisionBox(const std::string& uid, const Transform& transform, const Rectangle<float>& rectangle);
    void updateCollisionRectangle(const Rectangle<float>& rectangle);
    void tryCollideWith(CollisionBox& other);
    bool isColliding();
    bool isColliding(const std::string& collisionId);

   private:
    const std::string uid;
    const Transform& bindedTransform;
    Rectangle<float> rectangle;
    std::set<std::string> collisions;
};

}  // namespace Engine
