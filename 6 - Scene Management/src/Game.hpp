#ifndef Game_hpp
#define Game_hpp

#include <SFML/Graphics.hpp>

#include "WorkingDirectory.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include "SceneManager.hpp"
#include "SceneSplashScreen.hpp"
#include "SceneGame.hpp"

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
    
    sf::Clock clock;
    float deltaTime;
    
    Input input;
    SceneManager sceneManager;
};

#endif /* Game_hpp */
