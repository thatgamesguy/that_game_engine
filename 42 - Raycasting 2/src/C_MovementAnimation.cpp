#include "C_MovementAnimation.hpp"
#include "Object.hpp"

C_MovementAnimation::C_MovementAnimation(Object* owner) : Component(owner) { }

void C_MovementAnimation::Awake()
{
    velocity = owner->GetComponent<C_Velocity>();
    animation = owner->GetComponent<C_Animation>();
}

void C_MovementAnimation::Update(float deltaTime)
{
    if(animation->GetAnimationState() != AnimationState::Projectile)
    {
        const sf::Vector2f& currentVel = velocity->Get();
        
        if(currentVel.x != 0.f || currentVel.y != 0.f)
        {
            animation->SetAnimationState(AnimationState::Walk);
        }
        else
        {
            animation->SetAnimationState(AnimationState::Idle);
        }
    }
}
