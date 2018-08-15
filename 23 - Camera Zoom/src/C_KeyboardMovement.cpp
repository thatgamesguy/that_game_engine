#include "C_KeyboardMovement.hpp"
#include "Object.hpp"

C_KeyboardMovement::C_KeyboardMovement(Object* owner) : Component(owner), moveSpeed(400) {}

void C_KeyboardMovement::Awake()
{
    animation = owner->GetComponent<C_Animation>();
}

void C_KeyboardMovement::SetInput(Input* input)
{
    this->input = input;
}

void C_KeyboardMovement::SetMovementSpeed(int moveSpeed)
{
    this->moveSpeed = moveSpeed;
}

void C_KeyboardMovement::Update(float deltaTime)
{
    if(input == nullptr)
    {
        return;
    }
    
    int xMove = 0;
    if(input->IsKeyPressed(Input::Key::Left))
    {
        xMove = -moveSpeed;
        animation->SetAnimationDirection(FacingDirection::Left);
    }
    else if(input->IsKeyPressed(Input::Key::Right))
    {
        xMove = moveSpeed;
        animation->SetAnimationDirection(FacingDirection::Right);
    }
    
    int yMove = 0;
    if(input->IsKeyPressed(Input::Key::Up))
    {
        yMove = -moveSpeed;
    }
    else if(input->IsKeyPressed(Input::Key::Down))
    {
        yMove = moveSpeed;
    }
    
    float xFrameMove = xMove * deltaTime;
    float yFrameMove = yMove * deltaTime;
    
    owner->transform->AddPosition(xFrameMove, yFrameMove);
    
    if(xMove == 0 && yMove == 0)
    {
        animation->SetAnimationState(AnimationState::Idle);
    }
    else
    {
        animation->SetAnimationState(AnimationState::Walk);
    }
}
