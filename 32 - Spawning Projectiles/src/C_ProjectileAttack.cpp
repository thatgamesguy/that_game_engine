#include "C_ProjectileAttack.hpp"
#include "Object.hpp"

C_ProjectileAttack::C_ProjectileAttack(Object* owner) : Component(owner) {}

void C_ProjectileAttack::Awake()
{
    animation = owner->GetComponent<C_Animation>();
}

void C_ProjectileAttack::Start()
{
    projectileTextureID = textureAllocator->Add(workingDirectory->Get() + "LPC/Weapons/arrow.png");
}

void C_ProjectileAttack::Update(float deltaTime)
{
    if(input->IsKeyDown(Input::Key::E))
    {
        SpawnProjectile();
        animation->SetAnimationState(AnimationState::Projectile);
    }
    else if (input->IsKeyUp(Input::Key::E))
    {
        animation->SetAnimationState(AnimationState::Idle);
    }
}

void C_ProjectileAttack::SetInput(Input* input)
{
    this->input = input;
}

void C_ProjectileAttack::SetObjectCollection(ObjectCollection* objects)
{
    this->objects = objects;
}

void C_ProjectileAttack::SetWorkingDirectory(WorkingDirectory* workingDirectory)
{
    this->workingDirectory = workingDirectory;
}

void C_ProjectileAttack::SetTextureAllocator(ResourceAllocator<sf::Texture>* textureAllocator)
{
    this->textureAllocator = textureAllocator;
}

void C_ProjectileAttack::SpawnProjectile()
{
    std::shared_ptr<Object> projectile = std::make_shared<Object>();
    
    projectile->transform->SetPosition(owner->transform->GetPosition());
    
    auto projSprite = projectile->AddComponent<C_Sprite>();
    projSprite->SetTextureAllocator(textureAllocator);
    projSprite->Load(projectileTextureID);
    projSprite->SetDrawLayer(DrawLayer::Entities);
    projSprite->SetSortOrder(100);
    
    objects->Add(projectile);
}
