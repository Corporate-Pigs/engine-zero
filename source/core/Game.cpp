#include "engine-zero/core/Game.h"

Engine::Game::~Game() {}

void Engine::Game::start(Context *context) { onStart(context); }

void Engine::Game::update(Context *context) {
    mActiveScene->update(context);

    if (mActiveScene->didFinish()) {
        // TODO: i need to find a better way of passing these results around
        auto sceneResult = mActiveScene->getResult();
        if (sceneResult.mShouldExitProgram) {
            context->ui->exit();
        } else {
            context->graphics->flush();
            mActiveScene->destroy(context);
            mActiveScene.reset(getSceneFromResult(&sceneResult));
            mActiveScene->start(context, &sceneResult);
        }
    }
}

void Engine::Game::render(Context *context) { mActiveScene->render(context); }

void Engine::Game::destroy(Context *context) { mActiveScene->destroy(context); }
