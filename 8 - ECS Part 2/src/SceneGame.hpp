#ifndef SceneGame_hpp
#define SceneGame_hpp

#include <memory>

#include "Scene.hpp"
#include "Input.hpp"
#include "WorkingDirectory.hpp"
#include "Object.hpp"
#include "C_Sprite.hpp"
#include "C_KeyboardMovement.hpp"

class SceneGame : public Scene
{
public:
    SceneGame(WorkingDirectory& workingDir);
    
    void OnCreate() override;
    void OnDestroy() override;
    
    void ProcessInput() override;
    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override;
    void Draw(Window& window) override;
    
private:
    std::shared_ptr<Object> player;
    
    WorkingDirectory& workingDir;
    Input input;
};

#endif /* SceneGame_hpp */
