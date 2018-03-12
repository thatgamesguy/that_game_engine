#ifndef SceneGame_hpp
#define SceneGame_hpp

#include "Scene.hpp"
#include "Input.hpp"
#include "WorkingDirectory.hpp"

class SceneGame : public Scene
{
public:
    SceneGame(Input& input, WorkingDirectory& workingDir);
    
    void OnCreate() override;
    void OnDestroy() override;
    
    void Update(float deltaTime) override;
    void Draw(Window& window) override;
    
private:
    sf::Texture vikingTexture;
    sf::Sprite vikingSprite;
    
    WorkingDirectory& workingDir;
    Input& input;
};

#endif /* SceneGame_hpp */
