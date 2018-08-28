#include "C_ProjectileAttack.hpp"
#include "Object.hpp"

C_ProjectileAttack::C_ProjectileAttack(Object* owner) : Component(owner) {}

void C_ProjectileAttack::Awake()
{
    animation = owner->GetComponent<C_Animation>();
}

void C_ProjectileAttack::Start()
{
    projectileTextureID = owner->context->textureAllocator->Add(owner->context->workingDir->Get() + "LPC/Weapons/arrow.png");
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
    
    auto projSprite = projectile->AddComponent<C_Sprite>();
    projSprite->Load(projectileTextureID);
    projSprite->SetDrawLayer(DrawLayer::Entities);
    projSprite->SetSortOrder(100);
    
    owner->context->objects->Add(projectile);
}
