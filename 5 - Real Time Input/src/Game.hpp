#ifndef Game_hpp
#define Game_hpp

#include <SFML/Graphics.hpp>

#include "WorkingDirectory.hpp"
#include "Window.hpp"
#include "Input.hpp"

class Game
{
public:
    Game();
    
    void ProcessInput();
    void Update();
    void LateUpdate();
    void Draw();
    void CalculateDeltaTime();
    bool IsRunning() const;
    
private:
    Window window;
    WorkingDirectory workingDir;
    
    sf::Texture vikingTexture;
    sf::Sprite vikingSprite;

    sf::Clock clock;
    float deltaTime;
    
    Input input;
};

#endif /* Game_hpp */
