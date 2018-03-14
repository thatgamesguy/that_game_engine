#include "SceneGame.hpp"

SceneGame::SceneGame(WorkingDirectory& workingDir) : workingDir(workingDir)
{
    
}

void SceneGame::OnCreate()
{
    player = std::make_shared<Object>();
    
    auto sprite = player->AddComponent<C_Sprite>();
    sprite->Load(workingDir.Get() + "viking.png");
    
    auto movement = player->AddComponent<C_KeyboardMovement>();
    movement->SetInput(&input);
}

void SceneGame::OnDestroy()
{
    
}

void SceneGame::ProcessInput()
{
    input.Update();
}

void SceneGame::Update(float deltaTime)
{
    player->Update(deltaTime);
}

void SceneGame::LateUpdate(float deltaTime)
{
    player->LateUpdate(deltaTime);
}

void SceneGame::Draw(Window& window)
{
    player->Draw(window);
}
