#include "Game.hpp"

int main()
{
    Game game;
    
    while (game.IsRunning())
    {
        game.Update();
        game.LateUpdate();
        game.Draw();
    }
    
    return 0;
}
