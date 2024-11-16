#include "engine-zero/graphics/Rectangle.h"


Engine::Rectangle::Rectangle(): position(0.0f, 0.0f), size(0.0f, 0.0f) {}
Engine::Rectangle::Rectangle(float x, float y, float width, float height): position(x, y), size(width, height) {}

bool Engine::Rectangle::isIntersecting(const Engine::Rectangle& other) {
    bool overlapX = (position.x < other.position.x + other.size.x) && (position.x + size.x > other.position.x);
    bool overlapY = (position.y < other.position.y + other.size.y) && (position.y + size.y > other.position.y);
    return overlapX && overlapY;
}
