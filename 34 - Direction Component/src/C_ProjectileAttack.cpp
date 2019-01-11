#include "C_ProjectileAttack.hpp"
#include "Object.hpp"

std::unordered_map<FacingDirection, sf::IntRect, EnumClassHash> C_ProjectileAttack::textureDirectionBindings = {};

C_ProjectileAttack::C_ProjectileAttack(Object* owner) : Component(owner) {}

void C_ProjectileAttack::Awake()
{
    animation = owner->GetComponent<C_Animation>();
    direction = owner->GetComponent<C_Direction>();
}

void C_ProjectileAttack::Start()
{
    projectileTextureID = owner->context->textureAllocator->Add(owner->context->workingDir->Get() + "LPC/Weapons/arrow.png");
    
    textureDirectionBindings.emplace(FacingDirection::Up, sf::IntRect(0, 0, 64, 64));
    textureDirectionBindings.emplace(FacingDirection::Left, sf::IntRect(64, 0, 64, 64));
    textureDirectionBindings.emplace(FacingDirection::Down, sf::IntRect(128, 0, 64, 64));
    textureDirectionBindings.emplace(FacingDirection::Right, sf::IntRect(192, 0, 64, 64));
}

void C_ProjectileAttack::Update(float deltaTime)
{
    if(owner->context->input->IsKeyDown(Input::Key::E))
    {
        SpawnProjectile();
        animation->SetAnimationState(AnimationState::Projectile);
    }
    else if (owner->context->input->IsKeyUp(Input::Key::E))
    {
        animation->SetAnimationState(AnimationState::Idle);
    }
}

void C_ProjectileAttack::SpawnProjectile()
{
    std::shared_ptr<Object> projectile = std::make_shared<Object>(owner->context);
    
    projectile->transform->SetPosition(owner->transform->GetPosition());
 
    FacingDirection currentDir = direction->Get();
    
    auto projSprite = projectile->AddComponent<C_Sprite>();
    projSprite->Load(projectileTextureID);
    projSprite->SetDrawLayer(DrawLayer::Entities);
    projSprite->SetSortOrder(100);
    projSprite->SetTextureRect(textureDirectionBindings.at(direction->Get()));
 
    owner->context->objects->Add(projectile);
}
