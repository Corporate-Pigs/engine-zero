#include "engine-zero/tilemap/TileMap.h"

#include "engine-zero/resource/ResourceManager.h"

static constexpr unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
static constexpr unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
static constexpr unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;
static constexpr unsigned ROTATED_HEXAGONAL_120_FLAG = 0x10000000;

Engine::TileMap::TileMap(const Transform& transform, const std::string& filePath)
    : Actor(0, transform), tiledTileMap(new Engine::TiledTileMap()) {
    // load tile map from json file
    TiledTileMap::fromJson(filePath, *tiledTileMap);

    // load tile sheets from json
    TiledTileSheet tiledTileSheet;
    for (const auto& tiledTileSet : tiledTileMap->tileSets) {
        if (tiledTileSheets.contains(tiledTileSet.source)) {
            continue;
        }
        TiledTileSheet::fromJson(tiledTileSet.source, tiledTileSheet);
        tiledTileSheets[tiledTileSet.source] = tiledTileSheet;
    }

    // setup dims
    mNumberOfColumns = tiledTileMap->width;
    mNumberOfRows = tiledTileMap->height;
    mTileHeight = tiledTileMap->tileHeight;
    mTileWidth = tiledTileMap->tileWidth;
}

void Engine::TileMap::onStart(Context* context) {
    // create tile map layers
    for (uint16_t layerIndex = 0; layerIndex < tiledTileMap->layers.size(); layerIndex++) {
        TiledTileMapLayer& layer = tiledTileMap->layers[layerIndex];
        mTileLayers.push_back(TileLayer());
        mTileLayers[layerIndex].tiles.reset(new Tile[tiledTileMap->width * tiledTileMap->height]);

        for (uint16_t tileIndex = 0; tileIndex < layer.data.size(); tileIndex++) {
            uint32_t globalTileId = layer.data[tileIndex];
            globalTileId &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG |
                              ROTATED_HEXAGONAL_120_FLAG);
            if (globalTileId == 0) continue;

            auto& tile = mTileLayers[layerIndex].tiles[tileIndex];

            // compute drawing position
            uint32_t tileRow = tileIndex / tiledTileMap->width;
            uint32_t tileColumn = tileIndex % tiledTileMap->width;
            tile.transform = {{tileColumn * mTileWidth * 1.0f, tileRow * mTileHeight * 1.0f}, transform.layer};

            // find sheet
            auto tileSetPtr = tiledTileMap->getTileSetPtrForTileId(globalTileId);
            auto& tileSheet = tiledTileSheets[tileSetPtr->source];

            // setup properties
            uint32_t sheetTileId = globalTileId - tileSetPtr->firstId;
            const auto& sheetTile = tileSheet.tiles[sheetTileId];
            for (const auto& property : sheetTile.properties) {
                tile.properties.push_back({property.name, property.value});
            }

            // setup sprite / animated sprite if applied
            Rectangle<int32_t> spriteRectangle;
            if (!sheetTile.keyframes.empty()) {
                tile.sprite = context->graphics->createAnimatedSprite(tileSetPtr->source, sheetTile.id);
            }

            // this isn't an animated sprite.
            if (tile.sprite == nullptr) {
                tileSheet.computeRectangleForTileId(sheetTileId, spriteRectangle);
                tile.sprite = context->graphics->createSprite(tileSheet.image, spriteRectangle);
            }

            // setup rigid bodies
            for (const auto& object : sheetTile.objectGroup.objects) {
                if (object.type == "BoundingBox") {
                    tile.rigidBody = 
                        context->physics->createRigidBody(
                            nullptr, 
                            {tile.transform.position.x + object.x, tile.transform.position.y + object.y, object.width, object.height}, 
                            false);
                }
            }
        }
    }

    tiledTileMap.release();
    tiledTileSheets.clear();
}

void Engine::TileMap::onRender(Context* context) {
    const uint32_t mapSize = mNumberOfRows * mNumberOfColumns;

    for (int16_t li = mTileLayers.size() - 1; li > -1; li--) {
        const auto& layer = mTileLayers[li];
        for (uint16_t ti = 0; ti < mapSize; ti++) {
            const auto& tile = layer.tiles[ti];
            if (tile.sprite == nullptr) {
                continue;
            }
            context->graphics->render(*tile.sprite, tile.transform);
        }
    }
}

uint32_t Engine::TileMap::getTileHeight() { return mTileHeight; };

uint32_t Engine::TileMap::getTileWidth() { return mTileWidth; };