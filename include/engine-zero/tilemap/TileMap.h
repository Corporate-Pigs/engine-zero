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
    TileMap(const Transform& transform, const std::string& filePath);
    virtual void onStart(Context* context) override; 
    virtual void onRender(Context* context) override;

    uint32_t getTileHeight();
    uint32_t getTileWidth();

   private:
    std::unique_ptr<TiledTileMap> tiledTileMap;
    std::map<std::string, TiledTileSheet> tiledTileSheets;
    std::vector<TileLayer> mTileLayers;
    uint32_t mNumberOfColumns, mNumberOfRows, mTileHeight, mTileWidth;
};

}  // namespace Engine
