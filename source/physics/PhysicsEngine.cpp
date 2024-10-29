#include "engine-zero/physics/PhysicsEngine.h"

static constexpr auto k_gravity = 9.81f;
static constexpr auto k_nSteps = 1;

Engine::RigidBody* Engine::PhysicsEngine::createRigidBody(Transform* transform, bool isMovable) { 
    auto rb = new RigidBody(transform, isMovable);
    rigidBodies.push_back(std::unique_ptr<RigidBody>(rb));
    return rb; 
}

void Engine::PhysicsEngine::solveCollision(RigidBody* bodyA, RigidBody* bodyB) const {

    // horizontal overlap computing
    bool aIsToTheRight = bodyA->transform->mX > bodyB->transform->mX;
    RigidBody* rightBody = bodyA;
    RigidBody* leftBody = bodyB;
    if(!aIsToTheRight) {
        rightBody = bodyB;
        leftBody = bodyA;
    }
    auto rightBodyLeft = rightBody->transform->mX;
    auto leftBodyRight = leftBody->transform->mX + leftBody->transform->mWidth;
    auto horizontalOverlap = leftBodyRight - rightBodyLeft;
    if(horizontalOverlap < 0) horizontalOverlap = 0;
    
    // vertical overlap computing
    bool aIsOnTop =  bodyA->transform->mY < bodyB->transform->mY;
    RigidBody* topBody = bodyA;
    RigidBody* bottomBody = bodyB;
    if(!aIsOnTop) {
        topBody = bodyB;
        bottomBody = bodyA;
    }
    auto topBodyBottom = topBody->transform->mY + topBody->transform->mHeight;
    auto bottomBodyTop = bottomBody->transform->mY;
    auto verticalOverlap = topBodyBottom - bottomBodyTop;
    if(verticalOverlap < 0) verticalOverlap = 0;

    if(rightBody->isMovable() && leftBody->isMovable()) {
        horizontalOverlap *= 0.5f;
        verticalOverlap *= 0.5f;
    }

    if(horizontalOverlap < verticalOverlap) {
        if(rightBody->isMovable()) {
            rightBody->transform->mX += horizontalOverlap;
            rightBody->moveHorizontal(0.0f);
        }
        
        if(leftBody->isMovable()) {
            leftBody->transform->mX -= horizontalOverlap;
            leftBody->moveHorizontal(0.0f);
        }
    }
    else {
        if(topBody->isMovable()) {
            topBody->transform->mY -= verticalOverlap;
            topBody->isOnGround = true;
            //topBody->moveVertical(0.0f);
        }

        if(bottomBody->isMovable()) {
            bottomBody->transform->mY += verticalOverlap;
            bottomBody->isOnGround = true;
            //bottomBody->moveVertical(0.0f);
        }
    }

}

void Engine::PhysicsEngine::update(const double elapsedTime) {

    for(uint16_t step = 0; step < k_nSteps; step++) {

        for(const auto& rigidBody : rigidBodies) {
            if(!rigidBody->isMovable()) continue;
            rigidBody->applyGravity(k_gravity);
            rigidBody->update(elapsedTime);
        }

        for(const auto& rigidBody : rigidBodies) {
            rigidBody->isOnGround = false;
        }

        for(uint16_t indexA = 0; indexA < rigidBodies.size(); indexA++) {
            auto bodyA = rigidBodies[indexA].get();
            for(uint16_t indexB = indexA + 1; indexB < rigidBodies.size(); indexB++) {
                auto bodyB = rigidBodies[indexB].get();
                if(!bodyA->isMovable() && !bodyB->isMovable()) continue;
                if(bodyA->isIntersecting(*bodyB)){
                    solveCollision(bodyA, bodyB);
                }
            }
        }

    }

}