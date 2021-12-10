#include "SceneSplashScreen.hpp"

SceneSplashScreen::SceneSplashScreen(WorkingDirectory &workingDir, SceneStateMachine &sceneStateMachine, Window &window)
    : sceneStateMachine(sceneStateMachine), workingDir(workingDir), window(window), switchToState(0), currentSeconds(0.f), showForSeconds(3.f)
{
}

void SceneSplashScreen::OnCreate()
{
    splashTexture.loadFromFile(workingDir.Get() + "that_games_guy_logo.png");
    splashSprite.setTexture(splashTexture);

    sf::FloatRect spriteSize = splashSprite.getLocalBounds();
    splashSprite.setOrigin(spriteSize.width * 0.5f, spriteSize.height * 0.5f);
    splashSprite.setScale(0.5f, 0.5f);

    sf::Vector2u windowCentre = window.GetCentre();
    splashSprite.setPosition(windowCentre.x, windowCentre.y);
}

void SceneSplashScreen::OnActivate()
{
    currentSeconds = 0.f;
}

void SceneSplashScreen::OnDestroy() {}

void SceneSplashScreen::SetSwitchToScene(unsigned int id)
{
    switchToState = id;
}

void SceneSplashScreen::Update(float deltaTime)
{
    currentSeconds += deltaTime;

    if (currentSeconds >= showForSeconds)
    {
        sceneStateMachine.SwitchTo(switchToState);
    }
}

void SceneSplashScreen::Draw(Window &window)
{
    window.Draw(splashSprite);
}
