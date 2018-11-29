#include "SceneGame.hpp"

SceneGame::SceneGame(WorkingDirectory& workingDir, ResourceAllocator<sf::Texture>& textureAllocator, Window& window, ResourceAllocator<sf::Font>& fontAllocator) : workingDir(workingDir), textureAllocator(textureAllocator), mapParser(textureAllocator, context), window(window), objects(drawbleSystem, collisionSystem), collisionTree(5, 5, 0, {0, 0, 4200, 1080}, nullptr), collisionSystem(collisionTree), raycast(collisionTree), fontAllocator(fontAllocator) { }

void SceneGame::OnCreate()
{
    context.input = &input;
    context.objects = &objects;
    context.workingDir = &workingDir;
    context.textureAllocator = &textureAllocator;
    context.window = &window;
    context.raycast = &raycast;
    context.fontAllocator = &fontAllocator;
        
    CreatePlayer();
    CreateFriend();
    
    // You will need to play around with this offset until the level is in a suitable position based on the current window size.
    // This works for 1920 * 1080. In future we will remove this hardcoded offset when we add the ability to change resolutions.
   // sf::Vector2i mapOffset(0, 180);
    //sf::Vector2i mapOffset(128, 128);
    //std::vector<std::shared_ptr<Object>> levelTiles = mapParser.Parse(workingDir.Get() + "House Exterior.tmx", mapOffset);
    //objects.Add(levelTiles);
}

void SceneGame::OnDestroy()
{
    
}

void SceneGame::CreatePlayer()
{
    std::shared_ptr<Object> player = std::make_shared<Object>(&context);
    
    player->transform->SetPosition(100, 700);
    
    auto sprite = player->AddComponent<C_Sprite>();
    sprite->SetDrawLayer(DrawLayer::Entities);
    
    player->AddComponent<C_KeyboardMovement>();
    
    int textureID = textureAllocator.Add(workingDir.Get() + "Player.png");
    
    AddAnimationComponent(player, textureID);
    
    auto collider = player->AddComponent<C_BoxCollider>();
    collider->SetSize(64 * 0.4f, 64 * 0.5f);
    collider->SetOffset(0.f, 14.f);
    collider->SetLayer(CollisionLayer::Player);
    
    player->AddComponent<C_Camera>();
    player->AddComponent<C_ProjectileAttack>();
    player->AddComponent<C_Velocity>();
    player->AddComponent<C_MovementAnimation>();
    player->AddComponent<C_Direction>();
    player->AddComponent<C_InteractWithObjects>();
    
    objects.Add(player);
}

void SceneGame::CreateFriend()
{
    std::shared_ptr<Object> npc = std::make_shared<Object>(&context);
    
    npc->transform->SetPosition(160, 700);
    
    auto sprite = npc->AddComponent<C_Sprite>();
    sprite->SetDrawLayer(DrawLayer::Entities);
    
    const int textureID = textureAllocator.Add(workingDir.Get() + "Skeleton.png");
    
    AddAnimationComponent(npc, textureID);
    
    auto collider = npc->AddComponent<C_BoxCollider>();
    collider->SetSize(64 * 0.4f, 64 * 0.5f);
    collider->SetOffset(0.f, 14.f);
    collider->SetLayer(CollisionLayer::NPC);
    
    npc->AddComponent<C_Velocity>();
    npc->AddComponent<C_MovementAnimation>();
    npc->AddComponent<C_Direction>();
    npc->AddComponent<C_InteractableTalking>();
    
    objects.Add(npc);
}

void SceneGame::AddAnimationComponent(std::shared_ptr<Object> object, const int textureID)
{
    auto animation = object->AddComponent<C_Animation>();
    
    const unsigned int frameWidth =  64;
    const unsigned int frameHeight = 64;
    
    const FacingDirection directions[4] = {FacingDirection::Up, FacingDirection::Left, FacingDirection::Down, FacingDirection::Right};
    
    /*******************
     * Idle Animations *
     *******************/
    const bool idleAnimationLooped = false;
    
    unsigned int idleYFramePos = 512;
    
    std::unordered_map<FacingDirection, std::shared_ptr<Animation>, EnumClassHash> idleAnimations;
    
    for (int i = 0; i < 4; i++)
    {
        std::shared_ptr<Animation> idleAnimation = std::make_shared<Animation>();
        idleAnimation->SetLooped(idleAnimationLooped);
        idleAnimation->AddFrame(textureID, 0, idleYFramePos, frameWidth, frameHeight, 0.f);
        
        idleAnimations.insert(std::make_pair(directions[i], idleAnimation));
        
        idleYFramePos += frameHeight;
    }
    
    animation->AddAnimation(AnimationState::Idle, idleAnimations);
    
    
    /**********************
     * Walking Animations *
     **********************/
    const bool walkAnimationLooped = true;
    const int walkingFrameCount = 9;
    const float delayBetweenWalkingFramesSecs = 0.1f;
    
    unsigned int walkingYFramePos = 512;
    
    std::unordered_map<FacingDirection, std::shared_ptr<Animation>, EnumClassHash> walkingAnimations;
    
    for (int i = 0; i < 4; i++)
    {
        std::shared_ptr<Animation> walkingAnimation = std::make_shared<Animation>();
        walkingAnimation->SetLooped(walkAnimationLooped);
        for (int i = 0; i < walkingFrameCount; i++)
        {
            walkingAnimation->AddFrame(textureID, i * frameWidth, walkingYFramePos, frameWidth, frameHeight, delayBetweenWalkingFramesSecs);
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
    const float delayBetweenProjectileFramesSecs = 0.08f;
    
    std::unordered_map<FacingDirection, std::shared_ptr<Animation>, EnumClassHash> projectileAnimations;
    
    unsigned int projFrameYPos = 1024;
    
    for (int i = 0; i < 4; i++)
    {
        std::shared_ptr<Animation> projAnimation = std::make_shared<Animation>();
        projAnimation->SetLooped(projectileAnimationLooped);
        for (int i = 0; i < projectileFrameCount; i++)
        {
            projAnimation->AddFrame(textureID, i * frameWidth, projFrameYPos, frameWidth, frameHeight, delayBetweenProjectileFramesSecs);
        }
        projectileAnimations.insert(std::make_pair(directions[i], projAnimation));
        
        projFrameYPos += frameHeight;
    }
    
    animation->AddAnimation(AnimationState::Projectile, projectileAnimations);
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
