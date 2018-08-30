#include "C_KeyboardMovement.hpp"
#include "Object.hpp"

C_KeyboardMovement::C_KeyboardMovement(Object* owner) : Component(owner), moveSpeed(300.f) {}

void C_KeyboardMovement::Awake()
{
    animation = owner->GetComponent<C_Animation>();
    velocity = owner->GetComponent<C_Velocity>();
}

void C_KeyboardMovement::SetMovementSpeed(float moveSpeed)
{
    this->moveSpeed = moveSpeed;
}

void C_KeyboardMovement::Update(float deltaTime)
{
    //TODO: keyboardmovement should not interact with animation component.
    if(animation->GetAnimationState() == AnimationState::Projectile)
    {
        velocity->Set(0.f, 0.f);
        return;
    }
    
    float xMove = 0.f;
    if(owner->context->input->IsKeyPressed(Input::Key::Left))
    {
        xMove = -moveSpeed;
    }
    else if(owner->context->input->IsKeyPressed(Input::Key::Right))
    {
        xMove = moveSpeed;
    }
    
    float yMove = 0.f;
    if(owner->context->input->IsKeyPressed(Input::Key::Up))
    {
        yMove = -moveSpeed;
    }
    else if(owner->context->input->IsKeyPressed(Input::Key::Down))
    {
        yMove = moveSpeed;
    }
    
    velocity->Set(xMove, yMove);
}
