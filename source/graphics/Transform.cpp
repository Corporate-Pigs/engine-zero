#include "engine-zero/graphics/Transform.h"

Engine::Transform::Transform(float x, float y, float width, float height, uint16_t layer)
    : Rectangle(x, y, width, height), mLayer(layer) {}

void Engine::Transform::concatenate(const Transform& transform) {

}
