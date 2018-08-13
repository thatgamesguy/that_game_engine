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

    const int frameWidth =  64;
    const int frameHeight = 64;
    const int upYFramePos = 512;
    const int leftYFramePos = 576;
    const int downYFramePos = 640;
    const int rightYFramePos = 704;
    
    /*******************
     * Idle Animations *
     *******************/
    std::map<FacingDirection, std::shared_ptr<Animation>> idleAnimations;
    
    std::shared_ptr<Animation> idleUpAnimation = std::make_shared<Animation>();
    idleUpAnimation->AddFrame(playerTextureID, 0, upYFramePos, frameWidth, frameHeight, 0.f);
    idleAnimations.insert(std::make_pair(FacingDirection::Up, idleUpAnimation));
    
    std::shared_ptr<Animation> idleLeftAnimation = std::make_shared<Animation>();
    idleLeftAnimation->AddFrame(playerTextureID, 0, leftYFramePos, frameWidth, frameHeight, 0.f);
    idleAnimations.insert(std::make_pair(FacingDirection::Left, idleLeftAnimation));
    
    std::shared_ptr<Animation> idleDownAnimation = std::make_shared<Animation>();
    idleDownAnimation->AddFrame(playerTextureID, 0, downYFramePos, frameWidth, frameHeight, 0.f);
    idleAnimations.insert(std::make_pair(FacingDirection::Down, idleDownAnimation));
    
    std::shared_ptr<Animation> idleRightAnimation = std::make_shared<Animation>();
    idleRightAnimation->AddFrame(playerTextureID, 0, rightYFramePos, frameWidth, frameHeight, 0.f);
    idleAnimations.insert(std::make_pair(FacingDirection::Right, idleRightAnimation));

    animation->AddAnimation(AnimationState::Idle, idleAnimations);
    
    /**********************
     * Walking Animations *
     **********************/
    const int walkingFrameCount = 9;
    const float delayBetweenWalkingFramesSecs = 0.1f;
    
    std::map<FacingDirection, std::shared_ptr<Animation>> walkingAnimations;
    
    std::shared_ptr<Animation> walkUpAnimation = std::make_shared<Animation>();
    for (int i = 0; i < walkingFrameCount; i++)
    {
         walkUpAnimation->AddFrame(playerTextureID, i * frameWidth, upYFramePos, frameWidth, frameHeight, delayBetweenWalkingFramesSecs);
    }
    walkingAnimations.insert(std::make_pair(FacingDirection::Up, walkUpAnimation));
    
    std::shared_ptr<Animation> walkLeftAnimation = std::make_shared<Animation>();
    for (int i = 0; i < walkingFrameCount; i++)
    {
        walkLeftAnimation->AddFrame(playerTextureID, i * frameWidth, leftYFramePos, frameWidth, frameHeight, delayBetweenWalkingFramesSecs);
    }
    walkingAnimations.insert(std::make_pair(FacingDirection::Left, walkLeftAnimation));
    
    std::shared_ptr<Animation> walkDownAnimation = std::make_shared<Animation>();
    for (int i = 0; i < walkingFrameCount; i++)
    {
        walkDownAnimation->AddFrame(playerTextureID, i * frameWidth, downYFramePos, frameWidth, frameHeight, delayBetweenWalkingFramesSecs);
    }
    walkingAnimations.insert(std::make_pair(FacingDirection::Down, walkDownAnimation));
    
    std::shared_ptr<Animation> walkRightAnimation = std::make_shared<Animation>();
    for (int i = 0; i < walkingFrameCount; i++)
    {
        walkRightAnimation->AddFrame(playerTextureID, i * frameWidth, rightYFramePos, frameWidth, frameHeight, delayBetweenWalkingFramesSecs);
    }
    walkingAnimations.insert(std::make_pair(FacingDirection::Right, walkRightAnimation));
    
    
     animation->AddAnimation(AnimationState::Walk, walkingAnimations);
    
    auto collider = player->AddComponent<C_BoxCollider>();
    collider->SetSize(frameWidth * 0.4f, frameHeight * 0.5f);
    collider->SetOffset(0.f, 14.f);
    collider->SetLayer(CollisionLayer::Player);
    
    auto camera = player->AddComponent<C_Camera>();
    camera->SetWindow(&window);
    
    objects.Add(player);
    
    // You will need to play around with this offset until it fits the level in at your chosen resolution. This worls for 1920 * 1080.
    // In future we will remove this hardcoded offset when we look at allowing the player to change resolutions.
    sf::Vector2i mapOffset(-160, 180);
    //sf::Vector2i mapOffset(128, 128);
    std::vector<std::shared_ptr<Object>> levelTiles = mapParser.Parse(workingDir.Get() + "Test Map 1.tmx", mapOffset);
    
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
