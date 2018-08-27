#include "C_ProjectileAttack.hpp"
#include "Object.hpp"

C_ProjectileAttack::C_ProjectileAttack(Object* owner) : Component(owner) {}

void C_ProjectileAttack::Awake()
{
    animation = owner->GetComponent<C_Animation>();
}

void C_ProjectileAttack::Update(float deltaTime)
{
    if(input->IsKeyPressed(Input::Key::E))
    {
        animation->SetAnimationState(AnimationState::Projectile);
    }
}

void C_ProjectileAttack::SetInput(Input* input)
{
    this->input = input;
}
