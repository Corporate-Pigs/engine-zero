#pragma once

#include <cppvec/vec2.h>

#include "engine-zero/graphics/Transform.h"

namespace Engine {

class RigidBody {
   public:
   private:
    cppvec::Vec2 speed;
    cppvec::Vec2 acceleration;
    Transform* transform;
};

}  // namespace Engine
