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
    
    unsigned int Add(std::shared_ptr<Scene> scene);
    void SwitchTo(unsigned int id);
    void Remove(unsigned int id);
    
private:
    std::unordered_map<unsigned int, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> curScene;
    unsigned int insertedSceneID;
};

#endif /* SceneStateMachine_hpp */
