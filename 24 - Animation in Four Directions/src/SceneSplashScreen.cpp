#include "SceneSplashScreen.hpp"

SceneSplashScreen::SceneSplashScreen(WorkingDirectory& workingDir, SceneStateMachine& sceneStateMachine, Window& window, ResourceAllocator<sf::Texture>& textureAllocator) : sceneStateMachine(sceneStateMachine), workingDir(workingDir), window(window), switchToState(0), currentSeconds(0.f), showForSeconds(1.f), textureAllocator(textureAllocator)
{
    
}

void SceneSplashScreen::OnCreate()
{
    int textureID = textureAllocator.Add(workingDir.Get() + "that_games_guy_logo.png");
    
    if(textureID >= 0)
    {
        std::shared_ptr<sf::Texture> texture = textureAllocator.Get(textureID);
        splashSprite.setTexture(*texture);
        
        sf::FloatRect spriteSize = splashSprite.getLocalBounds();
        splashSprite.setOrigin(spriteSize.width * 0.5f, spriteSize.height * 0.5f);
        
        sf::Vector2f windowCentre = window.GetCentre();
        splashSprite.setPosition(windowCentre.x, windowCentre.y);
    }
}

void SceneSplashScreen::OnActivate()
{
    currentSeconds = 0.f;
}

void SceneSplashScreen::OnDestroy() { }

void SceneSplashScreen::SetSwitchToScene(unsigned int id)
{
    switchToState = id;
}

void SceneSplashScreen::Update(float deltaTime)
{
    currentSeconds += deltaTime;
    
    if(currentSeconds >= showForSeconds)
    {
        sceneStateMachine.SwitchTo(switchToState);
    }
}

void SceneSplashScreen::Draw(Window& window)
{
    window.Draw(splashSprite);
}
