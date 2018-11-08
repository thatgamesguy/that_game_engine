#ifndef SceneGame_hpp
#define SceneGame_hpp

#include "Scene.hpp"
#include "Input.hpp"
#include "WorkingDirectory.hpp"
#include "Object.hpp"
#include "C_Sprite.hpp"
#include "C_KeyboardMovement.hpp"
#include "ResourceAllocator.hpp"
#include "ObjectCollection.hpp"
#include "TileMapParser.hpp"
#include "C_Animation.hpp"
#include "C_BoxCollider.hpp"
#include "Debug.hpp"
#include "C_Camera.hpp"
#include "C_ProjectileAttack.hpp"
#include "C_Velocity.hpp"
#include "C_MovementAnimation.hpp"
#include "C_Direction.hpp"

class SceneGame : public Scene
{
public:
    SceneGame(WorkingDirectory& workingDir, ResourceAllocator<sf::Texture>& textureAllocator, Window& window);
    
    void OnCreate() override;
    void OnDestroy() override;
    
    void ProcessInput() override;
    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override;
    void Draw(Window& window) override;
    
private:
    void CreatePlayer();
    void CreateFriend();
    
    WorkingDirectory& workingDir;
    Input input;
    ResourceAllocator<sf::Texture>& textureAllocator;
    ObjectCollection objects;
    TileMapParser mapParser;
    Window& window;
    SharedContext context;
};

#endif /* SceneGame_hpp */
