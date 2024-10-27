#pragma once

#include <cassert>
#include <fstream>
#include <istream>
#include <nlohmann/json.hpp>

namespace Engine {

class ResourceLoader {
   public:
    static void loadJsonFromFile(std::string path, nlohmann::json& json) {
        std::ifstream file(path);
        assert(file.is_open());
        file >> json;
        file.close();
    }
};

}  // namespace Engine
