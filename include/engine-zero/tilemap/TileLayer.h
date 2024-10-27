#pragma once

#include <memory>

#include "engine-zero/tilemap/Tile.h"

namespace Engine {

struct TileLayer {
    std::unique_ptr<Tile[]> tiles;
};

}