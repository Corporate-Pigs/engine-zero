#pragma once

#include <string>
#include <vector>
#include <variant>

#include "engine-zero/graphics/Renderable.h"
#include "engine-zero/physics/RigidBody.h"

namespace Engine {

struct Tile {

    struct Property {
        std::string name;
        std::variant<bool, std::string> value;
    };

    struct AnimationKeyframe {
        uint32_t tileId;
        double durationInSeconds;
    };

    bool isCollidable = false;
    Renderable* sprite = nullptr;
    RigidBody* rigidBody = nullptr;
    Transform transform;

    std::vector<Tile::Property> properties;
};

}  // namespace Engine
