#include "SceneStateMachine.hpp"

SceneStateMachine::SceneStateMachine() : scenes(0), curScene(0) { }

void SceneStateMachine::ProcessInput()
{
    if(curScene)
    {
        curScene->ProcessInput();
    }
}

void SceneStateMachine::Update(float deltaTime)
{
    if(curScene)    
    {
        curScene->Update(deltaTime);
    }
}

void SceneStateMachine::LateUpdate(float deltaTime)
{
    if(curScene)
    {
        curScene->LateUpdate(deltaTime);
    }
}

void SceneStateMachine::Draw(Window& window)
{
    if(curScene)
    {
        curScene->Draw(window);
    }
}

bool SceneStateMachine::Add(SceneType type, std::shared_ptr<Scene> scene)
{
    auto inserted = scenes.insert(std::make_pair(type, scene));
    
    if(inserted.second)
    {
        inserted.first->second->OnCreate();
    }
    
    return inserted.second;
}

void SceneStateMachine::SwitchTo(const SceneType& type)
{
    auto it = scenes.find(type);
    if(it != scenes.end())
    {
        if(curScene)
        {
            curScene->OnDeactivate();
        }
        
        curScene = it->second;
        
        curScene->OnActivate();
    }
}

void SceneStateMachine::Remove(const SceneType& type)
{
    auto it = scenes.find(type);
    if(it != scenes.end())
    {
        if(curScene == it->second)
        {
            curScene = nullptr;
        }
        
        it->second->OnDestroy();
        
        scenes.erase(it);
    }
}
