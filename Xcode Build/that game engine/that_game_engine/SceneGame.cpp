#include "SceneGame.hpp"

SceneGame::SceneGame(Input& input, WorkingDirectory& workingDir) : input(input), workingDir(workingDir)
{
    
}

void SceneGame::OnCreate()
{
    vikingTexture.loadFromFile(workingDir.Get() + "viking.png");
    vikingSprite.setTexture(vikingTexture);
}

void SceneGame::OnDestroy()
{
    
}

void SceneGame::Update(float deltaTime)
{
    const sf::Vector2f& spritePos = vikingSprite.getPosition();
    const int moveSpeed = 100;
    
    int xMove = 0;
    if(input.IsKeyPressed(Input::KEY::LEFT))
    {
        xMove = -moveSpeed;
    }
    else if(input.IsKeyPressed(Input::KEY::RIGHT))
    {
        xMove = moveSpeed;
    }
    
    int yMove = 0;
    if(input.IsKeyPressed(Input::KEY::UP))
    {
        yMove = -moveSpeed;
    }
    else if(input.IsKeyPressed(Input::KEY::DOWN))
    {
        yMove = moveSpeed;
    }
    
    float xFrameMove = xMove * deltaTime;
    float yFrameMove = yMove * deltaTime;
    
    vikingSprite.setPosition(spritePos.x + xFrameMove, spritePos.y + yFrameMove);
}

void SceneGame::Draw(Window& window)
{
    window.Draw(vikingSprite);
}
