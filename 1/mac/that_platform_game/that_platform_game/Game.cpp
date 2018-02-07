#include "Game.hpp"

Game::Game() : window("that platform game")
{
    tempTexture.loadFromFile(workingDir.Get() + "viking.png");
    tempSprite.setTexture(tempTexture);
    
    const sf::Vector2f& spritePos = tempSprite.getPosition();
    tempSprite.setPosition(-500, spritePos.y);
}

void Game::Update()
{
    window.Update();
    
    const sf::Vector2f& spritePos = tempSprite.getPosition();
    tempSprite.setPosition(spritePos.x + 1, spritePos.y);
}

void Game::LateUpdate()
{
    
}

void Game::Draw()
{
    window.BeginDraw();
    
    window.Draw(tempSprite);
    
    window.EndDraw();
}

bool Game::IsRunning() const
{
    return window.IsOpen();
}
