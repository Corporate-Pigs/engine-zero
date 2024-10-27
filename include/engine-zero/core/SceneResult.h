#pragma once

namespace Engine {

/*
 * Represents a result from a finished scene.
 */
struct SceneResult {
    bool mShouldExitProgram = false;
    int mNextSceneId = 0;
    int mNextLevelId = 0;
    int mGameOverScore = 0;
};
}  // namespace Engine
