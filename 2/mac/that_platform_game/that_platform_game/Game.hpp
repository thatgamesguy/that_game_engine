#ifndef Game_hpp
#define Game_hpp

#include <SFML/Graphics.hpp>

#include "WorkingDirectory.hpp"
#include "Window.hpp"

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
    WorkingDirectory workingDir;
    
    sf::Texture tempTexture;
    sf::Sprite tempSprite;
};

#endif /* Game_hpp */
