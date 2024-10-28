#pragma once

#include "engine-zero/physics/RigidBody.h"

namespace Engine {

struct Collision {
    RigidBody* bodyOneId;
    RigidBody* bodyTwoId;
};

}  // namespace Engine
