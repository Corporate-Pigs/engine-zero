#include "engine-zero/core/Scene.h"

Engine::Scene::~Scene() {}

void Engine::Scene::start(Context* context, SceneResult* result) {
    mResult = *result;
    mResult.mNextLevelId = 0;
    mResult.mNextSceneId = 0;
    mResult.mShouldExitProgram = false;
    for (auto& o : mActors) {
        o->start(context);
    }
    onStart(context);
}

void Engine::Scene::update(Context* context) {
    for (auto& o : mActors) {
        o->update(context);
    }
    onUpdate(context);
}

void Engine::Scene::render(Context* context) {
    for (auto& o : mActors) {
        o->render(context);
    }
    onRender(context);
}

void Engine::Scene::destroy(Context* context) {
    for (auto& o : mActors) {
        o->destroy(context);
    }
    onDestroy(context);
}

Engine::SceneResult Engine::Scene::getResult() { return mResult; }

void Engine::Scene::attachActor(Actor* object) { mActors.push_back(object); }
