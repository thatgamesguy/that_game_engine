#ifndef Game_hpp
#define Game_hpp

#include <SFML/Graphics.hpp>

#include "Window.hpp"
#include <iostream>

class Game
{
public:
    Game();
    
    void Update();
    void LateUpdate();
    void Draw();
    bool IsRunning() const;
    
private:
    Window window;
};

#endif /* Game_hpp */
