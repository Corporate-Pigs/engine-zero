#pragma once

#include <SDL.h>
#include <cassert>

#include "engine-zero/graphics/Transform.h"

void rectangleToSDLRect(const Engine::Rectangle* inRectangle, SDL_Rect* outRect) {
    assert(inRectangle);
    assert(outRect);
    outRect->x = static_cast<int>(inRectangle->mX);
	outRect->y = static_cast<int>(inRectangle->mY);
	outRect->w = static_cast<int>(inRectangle->mWidth);
	outRect->h = static_cast<int>(inRectangle->mHeight);
}

void rectangleToSDLFRect(const Engine::Rectangle* inRectangle, SDL_FRect* outRect) {
    assert(inRectangle);
    assert(outRect);
    outRect->x = inRectangle->mX;
	outRect->y = inRectangle->mY;
	outRect->w = inRectangle->mWidth;
	outRect->h = inRectangle->mHeight;
}