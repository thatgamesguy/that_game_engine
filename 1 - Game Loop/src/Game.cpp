#include "Game.hpp"

Game::Game() : window("that platform game")
{
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
}

bool Game::IsRunning() const
{
    return window.IsOpen();
}
