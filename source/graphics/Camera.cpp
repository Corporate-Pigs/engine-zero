#include "engine-zero/graphics/Camera.h"

Engine::Camera::Camera(const Rectangle& initialPosition) : rectangle(initialPosition) {}

void Engine::Camera::moveTo(float x, float y) {
    rectangle.position = { x, y };
}