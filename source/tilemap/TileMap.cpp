#include "engine-zero/tilemap/TileMap.h"

#include "engine-zero/resource/ResourceManager.h"

static constexpr unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
static constexpr unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
static constexpr unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;
static constexpr unsigned ROTATED_HEXAGONAL_120_FLAG = 0x10000000;

Engine::TileMap::TileMap(const Transform& transform, uint16_t nVisibleColumns, uint16_t nVisibleRows)
    : Actor(0, transform), nVisibleColumns(nVisibleColumns), nVisibleRows(nVisibleRows) {}

void Engine::TileMap::buildFromTiledJson(const std::string& filePath, TileMap& tileMap, Context* context) {
    // load tile map from json file
    TiledTileMap tiledTileMap;
    TiledTileMap::fromJson(filePath, tiledTileMap);

    // load tile sheets from json
    TiledTileSheet tiledTileSheet;
    std::map<std::string, TiledTileSheet> tiledTileSheets;
    for (const auto& tiledTileSet : tiledTileMap.tileSets) {
        if (tiledTileSheets.contains(tiledTileSet.source)) {
            continue;
        }
        TiledTileSheet::fromJson(tiledTileSet.source, tiledTileSheet);
        tiledTileSheets[tiledTileSet.source] = tiledTileSheet;
    }

    // setup dims
    tileMap.mNumberOfColumns = tiledTileMap.width;
    tileMap.mNumberOfRows = tiledTileMap.height;
    tileMap.mTileHeight = tileMap.transform.mHeight / tileMap.nVisibleRows;
    tileMap.mTileWidth = tileMap.transform.mWidth / tileMap.nVisibleColumns;

    // create tile map layers
    for (uint16_t layerIndex = 0; layerIndex < tiledTileMap.layers.size(); layerIndex++) {
        TiledTileMapLayer& layer = tiledTileMap.layers[layerIndex];
        tileMap.mTileLayers.push_back(TileLayer());
        tileMap.mTileLayers[layerIndex].tiles.reset(new Tile[tiledTileMap.width * tiledTileMap.height]);

        for (uint16_t tileIndex = 0; tileIndex < layer.data.size(); tileIndex++) {
            uint32_t globalTileId = layer.data[tileIndex];
            globalTileId &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG |
                              ROTATED_HEXAGONAL_120_FLAG);
            if (globalTileId == 0) continue;

            auto& tile = tileMap.mTileLayers[layerIndex].tiles[tileIndex];

            // compute drawing position
            uint32_t tileRow = tileIndex / tiledTileMap.width;
            uint32_t tileColumn = tileIndex % tiledTileMap.width;
            tile.transform = {tileColumn * tileMap.mTileWidth, tileRow * tileMap.mTileHeight, tileMap.mTileWidth,
                              tileMap.mTileHeight, tileMap.transform.mLayer};

            // find sheet
            auto tileSetPtr = tiledTileMap.getTileSetPtrForTileId(globalTileId);
            auto& tileSheet = tiledTileSheets[tileSetPtr->source];

            // setup properties
            uint32_t sheetTileId = globalTileId - tileSetPtr->firstId;
            const auto& sheetTile = tileSheet.tiles[sheetTileId];
            for (const auto& property : sheetTile.properties) {
                tile.properties.push_back({property.name, property.value});
            }

            // setup sprite / animated sprite if applied
            Rectangle spriteRectangle;
            if (!sheetTile.keyframes.empty()) {
                auto animatedSprite = new AnimatedSprite();
                for (const auto& keyframe : sheetTile.keyframes) {
                    tileSheet.computeRectangleForTileId(keyframe.tileId, spriteRectangle);
                    animatedSprite->addKeyframe(
                        {context->graphics->createSprite(tileSheet.image, spriteRectangle), keyframe.duration});
                }
                tile.sprite = animatedSprite;
            }

            // this isn't an animated sprite.
            if (tile.sprite == nullptr) {
                tileSheet.computeRectangleForTileId(sheetTileId, spriteRectangle);
                tile.sprite = context->graphics->createSprite(tileSheet.image, spriteRectangle);
            }
        }
    }
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
            context->graphics->render(tile.sprite, &tile.transform);
        }
    }
}
