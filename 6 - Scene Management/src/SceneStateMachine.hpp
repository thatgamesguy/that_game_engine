#ifndef SceneStateMachine_hpp
#define SceneStateMachine_hpp

#include <memory>
#include <unordered_map>

#include "Scene.hpp"
#include "Window.hpp"
#include "EnumHash.hpp"

class SceneStateMachine
{
public:
    SceneStateMachine();
    
    void ProcessInput();
    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw(Window& window);
    
    bool Add(SceneType type, std::shared_ptr<Scene> scene);
    void SwitchTo(const SceneType& type);
    void Remove(const SceneType& type);
    
private:
    std::unordered_map<SceneType, std::shared_ptr<Scene>, EnumHash> scenes;
    std::shared_ptr<Scene> curScene;
};

#endif /* SceneStateMachine_hpp */
