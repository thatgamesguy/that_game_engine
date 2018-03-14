#ifndef SceneSplashScreen_hpp
#define SceneSplashScreen_hpp

#include <SFML/Graphics.hpp>

#include "SceneStateMachine.hpp"
#include "WorkingDirectory.hpp"

class SceneSplashScreen : public Scene
{
public:
    SceneSplashScreen(WorkingDirectory& workingDir, SceneStateMachine& sceneManager, Window& window, SceneType switchToState);
    
    void OnCreate() override;
    void OnDestroy() override;
    
    void OnActivate() override;
    
    void Update(float deltaTime) override;
    void Draw(Window& window) override;
    
private:
    sf::Texture splashTexture;
    sf::Sprite splashSprite;
    
    WorkingDirectory& workingDir;
    SceneStateMachine& sceneManager;
    Window& window;
    
    float currentSeconds;
    float showForSeconds;
    
    SceneType switchToState;
};

#endif /* SceneSplashScreen_hpp */
