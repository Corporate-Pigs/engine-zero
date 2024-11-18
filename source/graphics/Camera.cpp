#include "engine-zero/graphics/Camera.h"

Engine::Camera::Camera(const Rectangle<float>& initialPosition, const cppvec::Vec2<uint32_t>& windowSize) : rectangle(initialPosition), windowSize(windowSize) {
    
}

void Engine::Camera::moveTo(float x, float y) {
    rectangle.position = { x, y };
}

Engine::Transform Engine::Camera::getTransform() {
    return Transform(rectangle.position, { windowSize.x / rectangle.size.x, windowSize.y / rectangle.size.y}, 0);
}