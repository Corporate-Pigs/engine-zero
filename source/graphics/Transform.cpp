#include "engine-zero/graphics/Transform.h"

Engine::Transform::Transform(const cppvec::Vec2<float>& position, uint16_t layer)
    : position(position), scale(1.0f, 1.0f), layer(layer) {}

Engine::Transform::Transform(const cppvec::Vec2<float>& position, const cppvec::Vec2<float>& scale, uint16_t layer)
    : position(position), scale(scale), layer(layer) {}

Engine::Transform Engine::Transform::operator*(const Transform& other) const {
    // HACK: we need to change this into matrices
    auto rScale = scale * other.scale;
    return {(position * rScale) + (other.position * rScale), rScale, layer};
}
