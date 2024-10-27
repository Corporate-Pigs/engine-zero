#include <SDL.h>
#include <unordered_map>
#include <vector>

#include "engine-zero/ui/Input.h"

namespace Engine {

class SDLInputManager : public Engine::InputManager {
   public:
    SDLInputManager();

    virtual void setActionMapping(const std::unordered_map<std::string, InputKey>& keyBinds) override;

    virtual void setActionMapping(const std::string& action, const InputKey& key) override;

    virtual bool removeFromActionMapping(const std::string& action) override;
    
    virtual bool isPerformingAction(const std::string& action) const override;

    virtual void update(const SDL_Event& event, const double& currentTime);
   
   private:
    std::unordered_map<std::string, InputKey> inputMapping;
    std::unordered_map<InputKey, double> pressedKeys;
};
}  // namespace Engine