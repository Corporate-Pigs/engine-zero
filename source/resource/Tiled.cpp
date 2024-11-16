#include "engine-zero/resource/Tiled.h"

#include "engine-zero/resource/ResourceLoader.h"
#include "engine-zero/resource/ResourceManager.h"

void Engine::from_json(const nlohmann::json& j, TiledTileSheetTileObjectGroup& p) { j.at("objects").get_to(p.objects); }

void Engine::from_json(const nlohmann::json& j, TiledTileSheetTileObject& p) {
    j.at("id").get_to(p.id);
    j.at("x").get_to(p.x);
    j.at("y").get_to(p.y);
    j.at("height").get_to(p.height);
    j.at("width").get_to(p.width);
    j.at("type").get_to(p.type);
}

void Engine::from_json(const nlohmann::json& j, TiledTileSheetTileAnimationFrame& p) {
    j.at("duration").get_to(p.duration);
    p.duration /= 1000;
    j.at("tileid").get_to(p.tileId);
}

void Engine::from_json(const nlohmann::json& j, TiledTileSheetTileProperty& p) {
    j.at("name").get_to(p.name);
    auto value = j.at("value");

    if (value.is_boolean()) {
        p.value = value.get<bool>();
        return;
    }

    if (value.is_string()) {
        p.value = value.get<std::string>();
        return;
    }
}

void Engine::from_json(const nlohmann::json& j, TiledTileSheetTile& p) {
    j.at("id").get_to(p.id);
    if (j.contains("type")) {
        j.at("type").get_to(p.type);
    }
    if (j.contains("animation")) {
        j.at("animation").get_to(p.keyframes);
    }
    if (j.contains("properties")) {
        j.at("properties").get_to(p.properties);
    }
    if (j.contains("objectgroup")) {
        j.at("objectgroup").get_to(p.objectGroup);
    }
}

void Engine::from_json(const nlohmann::json& j, TiledTileSheet& p) {
    j.at("columns").get_to(p.columns);
    j.at("image").get_to(p.image);
    j.at("imageheight").get_to(p.imageHeight);
    j.at("imagewidth").get_to(p.imageWidth);
    j.at("tileheight").get_to(p.tileHeight);
    j.at("tilewidth").get_to(p.tileWidth);
    p.rows = p.imageHeight / p.tileHeight;
    if (j.contains("tiles")) {
        std::vector<TiledTileSheetTile> tiles;
        j.at("tiles").get_to(tiles);
        for (const auto& tile : tiles) {
            p.tiles[tile.id] = tile;
        }
    }
}

void Engine::from_json(const nlohmann::json& j, TiledTileMapLayerObject& p) {
    j.at("id").get_to(p.id);
    j.at("x").get_to(p.x);
    j.at("y").get_to(p.y);
}

void Engine::from_json(const nlohmann::json& j, TiledTileMapLayer& p) {
    j.at("id").get_to(p.id);
    j.at("name").get_to(p.name);
    if (j.contains("objects")) {
        j.at("objects").get_to(p.objects);
    }
    if (j.contains("data")) {
        j.at("data").get_to(p.data);
    }
}

void Engine::from_json(const nlohmann::json& j, TiledTileMapTileSet& p) {
    j.at("source").get_to(p.source);
    j.at("firstgid").get_to(p.firstId);
}

void Engine::from_json(const nlohmann::json& j, TiledTileMap& p) {
    j.at("tilewidth").get_to(p.tileWidth);
    j.at("width").get_to(p.width);
    j.at("tileheight").get_to(p.tileHeight);
    j.at("height").get_to(p.height);
    j.at("tilesets").get_to(p.tileSets);
    j.at("layers").get_to(p.layers);
}

void Engine::TiledTileMap::fromJson(std::string path, TiledTileMap& p) {
    nlohmann::json json;
    ResourceLoader::loadJsonFromFile(ResourceManager::getPathForGraphicsResource(path), json);
    p = json.get<Engine::TiledTileMap>();
}

const Engine::TiledTileMapTileSet* Engine::TiledTileMap::getTileSetPtrForTileId(uint32_t tileId) {
    for (int32_t i = tileSets.size() - 1; i > -1; i--) {
        auto& tileSet = tileSets[i];
        if (tileSet.firstId <= tileId) {
            return &tileSets[i];
        }
    }
    return nullptr;
}

void Engine::TiledTileSheet::fromJson(std::string path, TiledTileSheet& p) {
    nlohmann::json json;
    ResourceLoader::loadJsonFromFile(ResourceManager::getPathForGraphicsResource(path), json);
    p = json.get<Engine::TiledTileSheet>();
}

void Engine::TiledTileSheet::computeRectangleForTileId(uint32_t id, Rectangle& rectangle) const {
    uint32_t spriteRow = id / columns;
    uint32_t spriteColumn = id - (spriteRow * columns);
    rectangle.position = { static_cast<float>(spriteColumn * tileWidth), static_cast<float>(spriteRow * tileHeight) };
    rectangle.size = { static_cast<float>(tileWidth), static_cast<float>(tileHeight) };
}
