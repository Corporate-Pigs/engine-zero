#pragma once

namespace Engine {

/*
 * Represents the state of UI.
 * @param screenWidth The current width of the screen.
 * @param screenHeight The current height of the screen.
 * @param mouseX The current mouse position in X axis.
 * @param mouseY The current mouse position in Y axis.
 * @param mouseDragX The delta X of mouse drag.
 * @param mouseDragY The delta Y of mouse drag.
 * @param mouseClick Indicates if mouse was left clicked.
 */
class UIState {
   public:
    int screenWidth = 0, screenHeight = 0;
    float mouseX = 0, mouseY = 0;
    bool mouseDown = false;
    bool mouseHold = false;
};

}  // namespace Engine
