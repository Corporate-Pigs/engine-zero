#include "engine-zero/physics/PhysicsEngine.h"

static const cppvec::Vec2<float> k_gravity = {0.0f, 20.0f};
static constexpr auto k_nSteps = 10;

Engine::RigidBody* Engine::PhysicsEngine::createRigidBody(Transform* transform, const Rectangle<float> collisionBox,
                                                          bool isMovable) {
    auto rb = new RigidBody(transform, collisionBox, isMovable);
    rigidBodies.push_back(std::unique_ptr<RigidBody>(rb));
    return rb;
}

void Engine::PhysicsEngine::solveCollision(RigidBody* bodyA, RigidBody* bodyB) const {
    // horizontal overlap computing

    bodyA->isColliding = true;
    bodyB->isColliding = true;

    bool aIsToTheRight = bodyA->collisionBox.position.x > bodyB->collisionBox.position.x;
    RigidBody* rightBody = bodyA;
    RigidBody* leftBody = bodyB;
    if (!aIsToTheRight) {
        rightBody = bodyB;
        leftBody = bodyA;
    }
    auto rightBodyLeft = rightBody->collisionBox.position.x;
    auto leftBodyRight = leftBody->collisionBox.position.x + leftBody->collisionBox.size.x;
    auto horizontalOverlap = leftBodyRight - rightBodyLeft;
    if (horizontalOverlap < 0) horizontalOverlap = 0;

    // vertical overlap computing
    bool aIsOnTop = bodyA->collisionBox.position.y < bodyB->collisionBox.position.y;
    RigidBody* topBody = bodyA;
    RigidBody* bottomBody = bodyB;
    if (!aIsOnTop) {
        topBody = bodyB;
        bottomBody = bodyA;
    }
    auto topBodyBottom = topBody->collisionBox.position.y + topBody->collisionBox.size.y;
    auto bottomBodyTop = bottomBody->collisionBox.position.y;
    auto verticalOverlap = topBodyBottom - bottomBodyTop;
    if (verticalOverlap < 0) verticalOverlap = 0;

    if (rightBody->isMovable() && leftBody->isMovable()) {
        horizontalOverlap *= 0.5f;
        verticalOverlap *= 0.5f;
    }

    if (horizontalOverlap < verticalOverlap) {
        if (rightBody->isMovable()) {
            rightBody->move({horizontalOverlap, 0.0f});
            rightBody->setHorizontalSpeed(0.0f);
        }
        if (leftBody->isMovable()) {
            leftBody->move({-horizontalOverlap, 0.0f});
            leftBody->setHorizontalSpeed(0.0f);
        }
    } else {
        if (topBody->isMovable()) {
            topBody->move({0.0f, -verticalOverlap});
            topBody->setVerticalSpeed(0.0f);
        }
        if (bottomBody->isMovable()) {
            bottomBody->move({0.0f, verticalOverlap});
            bottomBody->setVerticalSpeed(0.0f);
        }
    }
}

void Engine::PhysicsEngine::update(const double elapsedTime) {
    for (uint16_t step = 0; step < k_nSteps; step++) {
        for (const auto& rigidBody : rigidBodies) {
            if (!rigidBody->isMovable()) continue;
            rigidBody->setAcceleration(k_gravity);
            rigidBody->update(elapsedTime);
            rigidBody->isColliding = false;
        }

        for (uint16_t indexA = 0; indexA < rigidBodies.size(); indexA++) {
            auto bodyA = rigidBodies[indexA].get();
            for (uint16_t indexB = indexA + 1; indexB < rigidBodies.size(); indexB++) {
                auto bodyB = rigidBodies[indexB].get();
                if (!bodyA->isMovable() && !bodyB->isMovable()) continue;
                if (bodyA->isIntersecting(*bodyB)) {
                    solveCollision(bodyA, bodyB);
                }
            }
        }
    }
}