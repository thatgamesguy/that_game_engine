#include "SceneManager.hpp"

SceneManager::SceneManager() : scenes(0), curScene(0) { }

void SceneManager::Update(float deltaTime)
{
    if(curScene)    
    {
        curScene->Update(deltaTime);
    }
}

void SceneManager::LateUpdate(float deltaTime)
{
    if(curScene)
    {
        curScene->LateUpdate(deltaTime);
    }
}

void SceneManager::Draw(Window& window)
{
    if(curScene)
    {
        curScene->Draw(window);
    }
}

bool SceneManager::Add(SceneType type, std::shared_ptr<Scene> scene)
{
    auto inserted = scenes.insert(std::make_pair(type, scene));
    
    if(inserted.second)
    {
        inserted.first->second->OnCreate();
    }
    
    return inserted.second;
}

void SceneManager::SwitchTo(const SceneType& type)
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

void SceneManager::Remove(const SceneType& type)
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
