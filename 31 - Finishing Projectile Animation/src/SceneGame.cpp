#include "SceneGame.hpp"

SceneGame::SceneGame(WorkingDirectory& workingDir, ResourceAllocator<sf::Texture>& textureAllocator, Window& window) : workingDir(workingDir), textureAllocator(textureAllocator), mapParser(textureAllocator), window(window) { }

void SceneGame::OnCreate()
{
    std::shared_ptr<Object> player = std::make_shared<Object>();
    
    player->transform->SetPosition(100, 700);
    
    auto sprite = player->AddComponent<C_Sprite>();
    sprite->SetTextureAllocator(&textureAllocator);
    sprite->SetDrawLayer(DrawLayer::Entities);
    
    auto movement = player->AddComponent<C_KeyboardMovement>();
    movement->SetInput(&input);
    
    auto animation = player->AddComponent<C_Animation>();
    
    int playerTextureID = textureAllocator.Add(workingDir.Get() + "Player.png");

    const unsigned int frameWidth =  64;
    const unsigned int frameHeight = 64;

    
    const FacingDirection directions[4] = {FacingDirection::Up, FacingDirection::Left, FacingDirection::Down, FacingDirection::Right};
    
    
    /*******************
     * Idle Animations *
     *******************/
    const bool idleAnimationLooped = false;
    
    unsigned int idleYFramePos = 512;
    
    std::map<FacingDirection, std::shared_ptr<Animation>> idleAnimations;
    
    for (int i = 0; i < 4; i++)
    {
        std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>();
        
        idleAnimation->AddFrame(playerTextureID, 0, idleYFramePos, frameWidth, frameHeight, 0.f, idleAnimationLooped);
        
        idleAnimations.insert(std::make_pair(directions[i], idleAnimation));
        
        idleYFramePos += frameHeight;
    }
    
    animation->AddAnimation(AnimationState::Idle, idleAnimations);
    
    
    /**********************
     * Walking Animations *
     **********************/
    const bool walkAnimationLooped = false;
    const int walkingFrameCount = 9;
    const float delayBetweenWalkingFramesSecs = 0.1f;
    
    unsigned int walkingYFramePos = 512;
    
    std::map<FacingDirection, std::shared_ptr<Animation>> walkingAnimations;
    
    for (int i = 0; i < 4; i++)
    {
        std::shared_ptr<Animation> walkingAnimation = std::make_shared<Animation>();
        for (int i = 0; i < walkingFrameCount; i++)
        {
            walkingAnimation->AddFrame(playerTextureID, i * frameWidth, walkingYFramePos, frameWidth, frameHeight, delayBetweenWalkingFramesSecs, walkAnimationLooped);
        }
        
        walkingAnimations.insert(std::make_pair(directions[i], walkingAnimation));
        
        walkingYFramePos += frameHeight;
    }
    
    animation->AddAnimation(AnimationState::Walk, walkingAnimations);
    
    
    /*************************
     * Projectile Animations *
     *************************/
    const bool projectileAnimationLooped = true;
    const int projectileFrameCount = 10;
    const float delayBetweenProjectileFramesSecs = 0.1f;

    std::map<FacingDirection, std::shared_ptr<Animation>> projectileAnimations;
    
    unsigned int projFrameYPos = 1024;
    
    for (int i = 0; i < 4; i++)
    {
        std::shared_ptr<Animation> projAnimation = std::make_shared<Animation>();
        for (int i = 0; i < projectileFrameCount; i++)
        {
            projAnimation->AddFrame(playerTextureID, i * frameWidth, projFrameYPos, frameWidth, frameHeight, delayBetweenProjectileFramesSecs, projectileAnimationLooped);
        }
        projectileAnimations.insert(std::make_pair(directions[i], projAnimation));
        
        projFrameYPos += frameHeight;
    }
    
    animation->AddAnimation(AnimationState::Projectile, projectileAnimations);

    
    auto collider = player->AddComponent<C_BoxCollider>();
    collider->SetSize(frameWidth * 0.4f, frameHeight * 0.5f);
    collider->SetOffset(0.f, 14.f);
    collider->SetLayer(CollisionLayer::Player);
    
    auto camera = player->AddComponent<C_Camera>();
    camera->SetWindow(&window);
    
    auto projectileAttack = player->AddComponent<C_ProjectileAttack>();
    projectileAttack->SetInput(&input);
    
    player->AddComponent<C_Velocity>();
    
    player->AddComponent<C_MovementAnimation>();
    
    objects.Add(player);
    
    // You will need to play around with this offset until it fits the level in at your chosen resolution. This worls for 1920 * 1080.
    // In future we will remove this hardcoded offset when we look at allowing the player to change resolutions.
    sf::Vector2i mapOffset(0, 180);
    //sf::Vector2i mapOffset(128, 128);
    std::vector<std::shared_ptr<Object>> levelTiles = mapParser.Parse(workingDir.Get() + "House Exterior.tmx", mapOffset);
    
    objects.Add(levelTiles);
}

void SceneGame::OnDestroy()
{
    
}

void SceneGame::ProcessInput()
{
    input.Update();
}

void SceneGame::Update(float deltaTime)
{
    objects.ProcessRemovals();
    objects.ProcessNewObjects();
    objects.Update(deltaTime);
    Debug::HandleCameraZoom(window, input);
}

void SceneGame::LateUpdate(float deltaTime)
{
    objects.LateUpdate(deltaTime);
}

void SceneGame::Draw(Window& window)
{
    objects.Draw(window);
    
    Debug::Draw(window);
}
