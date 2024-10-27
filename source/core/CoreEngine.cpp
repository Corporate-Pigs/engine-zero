#include "engine-zero/core/CoreEngine.h"

#include <cassert>
#include <chrono>

#include "engine-zero/sdl/SDLUserInterface.h"

#include "engine-zero/resource/Tiled.h"

Engine::CoreEngine::CoreEngine(std::shared_ptr<UserInterface> ui, std::shared_ptr<Game> game, Options options)
    : mGraphics(nullptr), mUI(ui), mGame(game), mOptions(options) {}

Engine::CoreEngine* Engine::CoreEngine::buildDefault(std::shared_ptr<Engine::Game> game,
                                                     Engine::Options* options) {
    // TODO: we need a factory here!
    auto ui = std::shared_ptr<UserInterface>(new Engine::SDLUserInterface(options));
    auto im = ui->getInputManager();
    im->setActionMapping("up", Engine::InputKey::K_w);
    im->setActionMapping("down", Engine::InputKey::K_s);
    im->setActionMapping("left", Engine::InputKey::K_a);
    im->setActionMapping("right", Engine::InputKey::K_d);

    return new Engine::CoreEngine(ui, game, *options);
}

void Engine::CoreEngine::start() {
    mUI->start();
    
    mGraphics.reset(mUI->enableGraphics());
    mGraphics->start();

    Context context(mGraphics.get(), mUI.get());

    mGame->start(&context);

    double previous = mUI->getTime();

    while (mUI->isRunning()) {
        double current = mUI->getTime();
        context.elapsedTime = current - previous;
        previous = current;

        // update window and handle input events
        mUI->update();

        // update game state
        mGame->update(&context);

        // render
        mGame->render(&context);
        mGraphics->render();
    }

    // TODO: evaluate moving those intro their respective destructors.
    mGame->destroy(&context);
    mGraphics->destroy();
    mUI->destroy();
}