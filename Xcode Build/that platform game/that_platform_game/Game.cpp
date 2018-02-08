#include "Game.hpp"

Game::Game() : window("that platform game")
{
    vikingTexture.loadFromFile(workingDir.Get() + "viking.png");
    vikingSprite.setTexture(vikingTexture);
    
    deltaTime = clock.restart().asSeconds();
}

void Game::Update()
{
    window.Update();

    const sf::Vector2f& spritePos = vikingSprite.getPosition();
    
    const int moveSpeed = 100;
    
    int xMove = 0;
    if(input.IsKeyPressed(sf::Keyboard::Left))
    {
        xMove = -moveSpeed;
    }
    else if (input.IsKeyPressed(sf::Keyboard::Right))
    {
        xMove = moveSpeed;
    }
    
    int yMove = 0;
    if(input.IsKeyPressed(sf::Keyboard::Up))
    {
        yMove = -moveSpeed;
    }
    else if(input.IsKeyPressed(sf::Keyboard::Down))
    {
        yMove = moveSpeed;
    }

    float xFrameMove = xMove * deltaTime;
    float yFrameMove = yMove * deltaTime;
    
    vikingSprite.setPosition(spritePos.x + xFrameMove, spritePos.y + yFrameMove);
}

void Game::LateUpdate()
{
    deltaTime = clock.restart().asSeconds();
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
