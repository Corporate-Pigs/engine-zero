#include "engine-zero/physics/PhysicsEngine.h"

static const cppvec::Vec2<float> k_gravity = {0.0f, 0.0f};
static constexpr auto k_nSteps = 1;

Engine::MovingBody* Engine::PhysicsEngine::createMovingBody(Transform& transform) {
    auto rb = new MovingBody(transform);
    movingBodies.push_back(std::unique_ptr<MovingBody>(rb));
    return rb;
}

Engine::CollisionBox* Engine::PhysicsEngine::createCollisionBox(const std::string& uid, const Transform& transform,
                                                                const Rectangle<float> collisionBox) {
    auto cb = new CollisionBox(uid, transform, collisionBox);
    collisionBoxes.push_back(std::unique_ptr<CollisionBox>(cb));
    return cb;
}

void Engine::PhysicsEngine::update(const double elapsedTime) {
    auto elpsedStep = elapsedTime / k_nSteps;
    for (uint16_t step = 0; step < k_nSteps; step++) {
        for (const auto& movingBody : movingBodies) {
            movingBody->update(elpsedStep);
        }

        for (uint16_t indexA = 0; indexA < collisionBoxes.size(); indexA++) {
            auto boxA = collisionBoxes[indexA].get();
            //boxA->update();
            for (uint16_t indexB = indexA + 1; indexB < collisionBoxes.size(); indexB++) {
                auto boxB = collisionBoxes[indexB].get();
                //boxB->update();
                boxA->tryCollideWith(*boxB);
            }
        }
    }
}