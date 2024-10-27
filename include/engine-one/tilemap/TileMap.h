#pragma once

#include <memory>

#include "engine-zero/core/Actor.h"
#include "engine-zero/graphics/AnimatedSprite.h"
#include "engine-zero/graphics/Sprite.h"
#include "engine-zero/resource/Tiled.h"
#include "engine-zero/tilemap/TileLayer.h"

namespace Engine {

class TileMap : public Engine::Actor {
   public:
    TileMap(const Transform& transform, uint16_t nVisibleColumns, uint16_t nVisibleRows);
    void onRender(Context* context) override;

    static void buildFromTiledJson(const std::string& filePath, TileMap& tileMap, Context* context);

   private:
    std::vector<TileLayer> mTileLayers;
    uint16_t nVisibleColumns;
    uint16_t nVisibleRows;
    uint32_t mNumberOfColumns, mNumberOfRows, mTileHeight, mTileWidth;
};

}  // namespace Engine
