#pragma once

#include <SDL.h>
#include <cassert>

#include "engine-zero/graphics/Transform.h"

void rectangleToSDLRect(const Engine::Rectangle<int32_t>& inRectangle, SDL_Rect& outRect) {
    outRect.x = inRectangle.position.x;
	outRect.y = inRectangle.position.y;
	outRect.w = inRectangle.size.x;
	outRect.h = inRectangle.size.y;
}

void transformToSDLFRect(const Engine::Transform& inTransform, SDL_FRect& outRect) {
    outRect.x = inTransform.position.x;
	outRect.y = inTransform.position.y;
	outRect.w *= inTransform.scale.x;
	outRect.h *= inTransform.scale.y;
}