#include "SceneStateMachine.hpp"

SceneStateMachine::SceneStateMachine() : scenes(0), curScene(0), insertedSceneID(0) { }

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

unsigned int SceneStateMachine::Add(std::shared_ptr<Scene> scene)
{
    auto inserted = scenes.insert(std::make_pair(insertedSceneID, scene));
    
    inserted.first->second->OnCreate();
    
    return insertedSceneID++;
}

void SceneStateMachine::SwitchTo(unsigned int id)
{
    auto it = scenes.find(id);
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

void SceneStateMachine::Remove(unsigned int id)
{
    auto it = scenes.find(id);
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
