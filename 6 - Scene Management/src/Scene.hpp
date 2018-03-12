#ifndef Scene_hpp
#define Scene_hpp

#include "Window.hpp"

enum class SceneType { SplashScreen, MainMenu, Game, Paused, GameOver, Credits };

class Scene
{
public:
    virtual void OnCreate() = 0; // Called when scene initially created. Called once per scene.
    virtual void OnDestroy() = 0; // Called when scene destroyed. Called once per scene.
    
    virtual void OnActivate() {}; // Called whenever a scene is activated.
    virtual void OnDeactivate() {}; // Called whenever a scene is deactivated.
    
    virtual void Update(float deltaTime) {};
    virtual void LateUpdate(float deltaTime) {};
    virtual void Draw(Window& window) {};
};

#endif /* Scene_hpp */
