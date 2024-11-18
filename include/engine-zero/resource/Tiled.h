#pragma once

#include <nlohmann/json.hpp>
#include <variant>

#include "engine-zero/graphics/Rectangle.h"

namespace Engine {

struct TiledTileSheetTileAnimationFrame {
    uint32_t tileId;
    double duration;
};

struct TiledTileSheetTileObject {
    float id, x, y, height, width;
    std::string type;
};

struct TiledTileSheetTileProperty {
    std::string name;
    std::variant<bool, std::string> value;
};

struct TiledTileSheetTileObjectGroup {
    std::vector<TiledTileSheetTileObject> objects;
};

struct TiledTileSheetTile {
    std::string type;
    uint32_t id;
    TiledTileSheetTileObjectGroup objectGroup;
    std::vector<TiledTileSheetTileProperty> properties;
    std::vector<TiledTileSheetTileAnimationFrame> keyframes;
};

struct TiledTileSheet {
    std::string image;
    uint32_t id, columns, rows, tileWidth, tileHeight, imageWidth, imageHeight;
    std::map<uint32_t, TiledTileSheetTile> tiles;
    static void fromJson(std::string path, TiledTileSheet& p);
    void computeRectangleForTileId(uint32_t id, Rectangle<int32_t>& rectangle) const;
};

struct TiledTileMapLayerObject {
    uint32_t id, x, y;
};

struct TiledTileMapLayer {
    uint32_t id;
    std::string name;
    std::vector<TiledTileMapLayerObject> objects;
    std::vector<uint32_t> data;
};

struct TiledTileMapTileSet {
    std::string source;
    uint32_t firstId;
};

struct TiledTileMap {
    uint32_t width, height, tileWidth, tileHeight;
    std::vector<TiledTileMapTileSet> tileSets;
    std::vector<TiledTileMapLayer> layers;

    static void fromJson(std::string path, TiledTileMap& p);
    const TiledTileMapTileSet* getTileSetPtrForTileId(uint32_t tileId);
};

void from_json(const nlohmann::json& j, TiledTileSheetTileAnimationFrame& p);

void from_json(const nlohmann::json& j, TiledTileSheetTile& p);

void from_json(const nlohmann::json& j, TiledTileSheetTileProperty& p);

void from_json(const nlohmann::json& j, TiledTileSheet& p);

void from_json(const nlohmann::json& j, TiledTileMapLayerObject& p);

void from_json(const nlohmann::json& j, TiledTileMapLayer& p);

void from_json(const nlohmann::json& j, TiledTileMapTileSet& p);

void from_json(const nlohmann::json& j, TiledTileMap& p);

void from_json(const nlohmann::json& j, TiledTileSheetTileObjectGroup& p);

void from_json(const nlohmann::json& j, TiledTileSheetTileObject& p);

}  // namespace Engine
