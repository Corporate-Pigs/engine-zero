#pragma once

#include <map>
#include <string>

namespace Engine {

class ResourceManager {
   public:
    static ResourceManager* getInstance();
    static std::string getPathForGraphicsResource(std::string resourceName);

   private:
    ResourceManager();
    ~ResourceManager();

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    std::string mBasePath, mGraphics;
    std::map<std::string, int> mResourceCache;
};

}  // namespace Engine