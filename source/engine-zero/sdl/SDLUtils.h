#pragma once

#include <SDL.h>
#include <cassert>

#include "engine-zero/graphics/Transform.h"

void rectangleToSDLRect(const Engine::Rectangle& inRectangle, SDL_Rect& outRect) {
    outRect.x = static_cast<int>(inRectangle.position.x);
	outRect.y = static_cast<int>(inRectangle.position.y);
	outRect.w = static_cast<int>(inRectangle.size.x);
	outRect.h = static_cast<int>(inRectangle.size.y);
}

void rectangleToSDLFRect(const Engine::Rectangle& inRectangle, SDL_FRect& outRect) {
    outRect.x = inRectangle.position.x;
	outRect.y = inRectangle.position.y;
	outRect.w = inRectangle.size.x;
	outRect.h = inRectangle.size.y;
}