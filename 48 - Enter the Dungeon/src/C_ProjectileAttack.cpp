#include "C_ProjectileAttack.hpp"
#include "Object.hpp"

std::unordered_map<FacingDirection, sf::IntRect, EnumClassHash> C_ProjectileAttack::textureDirectionBindings = {};
std::unordered_map<FacingDirection, sf::Vector2f, EnumClassHash> C_ProjectileAttack::offsetDirectionBindings = {};
std::unordered_map<FacingDirection, sf::Vector2f, EnumClassHash> C_ProjectileAttack::velocityDirectionBindings = {};

C_ProjectileAttack::C_ProjectileAttack(Object* owner) : Component(owner), projectileVelocity(500.f) {}

void C_ProjectileAttack::Awake()
{
    animation = owner->GetComponent<C_Animation>();
    direction = owner->GetComponent<C_Direction>();
}

void C_ProjectileAttack::Start()
{
    projectileTextureID = owner->context->textureAllocator->Add(owner->context->workingDir->Get() + "LPC/Weapons/arrow.png");
    
    textureDirectionBindings.emplace(FacingDirection::Up, sf::FloatRect(0, 0, 64, 64));
    textureDirectionBindings.emplace(FacingDirection::Left, sf::FloatRect(64, 0, 64, 64));
    textureDirectionBindings.emplace(FacingDirection::Down, sf::FloatRect(128, 0, 64, 64));
    textureDirectionBindings.emplace(FacingDirection::Right, sf::FloatRect(192, 0, 64, 64));
    
    offsetDirectionBindings.emplace(FacingDirection::Up, sf::Vector2f());
    offsetDirectionBindings.emplace(FacingDirection::Left, sf::Vector2f(-8.f, 3.f));
    offsetDirectionBindings.emplace(FacingDirection::Down, sf::Vector2f(-3.f, 15.f));
    offsetDirectionBindings.emplace(FacingDirection::Right, sf::Vector2f(8.f, 3.f));
    
    velocityDirectionBindings.emplace(FacingDirection::Up, sf::Vector2f(0.f, -1.f));
    velocityDirectionBindings.emplace(FacingDirection::Left, sf::Vector2f(-1.f, 0.f));
    velocityDirectionBindings.emplace(FacingDirection::Down, sf::Vector2f(0.f, 1.f));
    velocityDirectionBindings.emplace(FacingDirection::Right, sf::Vector2f(1.f, 0.f));
    
    animation->AddAnimationAction(AnimationState::Projectile, FacingDirection::Up, 9, std::bind(&C_ProjectileAttack::SpawnProjectile, this));
    animation->AddAnimationAction(AnimationState::Projectile, FacingDirection::Left, 9, std::bind(&C_ProjectileAttack::SpawnProjectile, this));
    animation->AddAnimationAction(AnimationState::Projectile, FacingDirection::Down, 9, std::bind(&C_ProjectileAttack::SpawnProjectile, this));
    animation->AddAnimationAction(AnimationState::Projectile, FacingDirection::Right, 9, std::bind(&C_ProjectileAttack::SpawnProjectile, this));
}

void C_ProjectileAttack::Update(float deltaTime)
{
    if(owner->context->input->IsKeyDown(Input::Key::E))
    {
        animation->SetAnimationState(AnimationState::Projectile);
    }
    else if (owner->context->input->IsKeyUp(Input::Key::E))
    {
        animation->SetAnimationState(AnimationState::Idle);
    }
}

void C_ProjectileAttack::SpawnProjectile()
{
    FacingDirection faceDir = direction->Get();
    
    std::shared_ptr<Object> projectile = std::make_shared<Object>(owner->context);
    
    projectile->transform->SetPosition(owner->transform->GetPosition() +
                                       offsetDirectionBindings.at(faceDir));
 
    auto projSprite = projectile->AddComponent<C_Sprite>();
    projSprite->Load(projectileTextureID);
    projSprite->SetDrawLayer(DrawLayer::Entities);
    projSprite->SetSortOrder(100);
    projSprite->SetTextureRect(textureDirectionBindings.at(faceDir));
    
    auto velocity = projectile->AddComponent<C_Velocity>();
    velocity->Set(velocityDirectionBindings.at(faceDir) * projectileVelocity);
    
    auto collider = projectile->AddComponent<C_BoxCollider>();
    collider->SetSize(32, 32);
    collider->SetLayer(CollisionLayer::Projectile);
    
    projectile->AddComponent<C_RemoveObjectOnCollisionEnter>();
 
    owner->context->objects->Add(projectile);
}
