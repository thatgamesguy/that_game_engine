#include "Game.hpp"

Game::Game() : window("that game engine")
{
    vikingTexture.loadFromFile(workingDir.Get() + "viking.png");
    vikingSprite.setTexture(vikingTexture);
}

void Game::Update()
{
    window.Update();
}

void Game::LateUpdate()
{

}

void Game::Draw()
{
    window.BeginDraw();
    
    window.Draw(vikingSprite);
    
    window.EndDraw();
}

bool Game::IsRunning() const
{
    return window.IsOpen();
}
