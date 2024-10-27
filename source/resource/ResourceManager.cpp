#include "engine-zero/resource/ResourceManager.h"

Engine::ResourceManager* Engine::ResourceManager::getInstance() { 
    static Engine::ResourceManager mInstance;
    return &mInstance;
};

std::string Engine::ResourceManager::getPathForGraphicsResource(std::string resourceName) {
    auto rm = Engine::ResourceManager::getInstance(); 
    return rm->mBasePath + rm->mGraphics + resourceName; 
}

Engine::ResourceManager::ResourceManager() : mBasePath("../assets/"), mGraphics("gtx/") {};

Engine::ResourceManager::~ResourceManager() {

};