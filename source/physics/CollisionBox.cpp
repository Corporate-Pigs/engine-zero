#include "engine-zero/physics/CollisionBox.h"

#include <algorithm>

Engine::CollisionBox::CollisionBox(const std::string& uid, const Transform& transform,
                                   const Rectangle<float>& rectangle)
    : uid(uid), bindedTransform(transform), rectangle(rectangle), originalPosition(rectangle.position) {
        this->rectangle.position += transform.position;
    }

void Engine::CollisionBox::update() {
    rectangle.position = originalPosition + bindedTransform.position; 
    printf("%f\n", rectangle.position.y);
}

void Engine::CollisionBox::updateCollisionRectangle(const Rectangle<float>& rectangle) { 
    this->rectangle = rectangle;
    originalPosition = rectangle.position;
};

void Engine::CollisionBox::tryCollideWith(CollisionBox& other) {
    if (!rectangle.isIntersecting(other.rectangle)) {
        return;
    }
    collisions.insert(other.uid);
    other.collisions.insert(uid);
}

bool Engine::CollisionBox::isColliding() { 
    return !collisions.empty(); 
}

bool Engine::CollisionBox::isColliding(const std::string& collisionId) {
    return std::find(collisions.begin(), collisions.end(), collisionId) != collisions.end();
}