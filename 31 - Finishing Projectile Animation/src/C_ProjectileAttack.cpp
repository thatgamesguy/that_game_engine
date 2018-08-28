#include "C_ProjectileAttack.hpp"
#include "Object.hpp"

C_ProjectileAttack::C_ProjectileAttack(Object* owner) : Component(owner) {}

void C_ProjectileAttack::Awake()
{
    animation = owner->GetComponent<C_Animation>();
}

void C_ProjectileAttack::Update(float deltaTime)
{
    if(input->IsKeyDown(Input::Key::E))
    {
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
