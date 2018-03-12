#include "Game.hpp"

Game::Game() : window("that game engine")
{
    std::shared_ptr<SceneSplashScreen> splashScreen = std::make_shared<SceneSplashScreen>(workingDir, sceneManager, window, SceneType::Game);
    
    sceneManager.Add(SceneType::SplashScreen, splashScreen);
    
    std::shared_ptr<SceneGame> gameScene = std::make_shared<SceneGame>(input, workingDir);
    
    sceneManager.Add(SceneType::Game, gameScene);
    
    sceneManager.SwitchTo(SceneType::SplashScreen);
    
    deltaTime = clock.restart().asSeconds();
}

void Game::ProcessInput()
{
    input.Update();
}

void Game::Update()
{
    window.Update();
    
    sceneManager.Update(deltaTime);
}

void Game::LateUpdate()
{
    sceneManager.LateUpdate(deltaTime);
}

void Game::Draw()
{
    window.BeginDraw();
    
    sceneManager.Draw(window);
    
    window.EndDraw();
}

void Game::CalculateDeltaTime()
{
    deltaTime = clock.restart().asSeconds();
}

bool Game::IsRunning() const
{
    return window.IsOpen();
}
