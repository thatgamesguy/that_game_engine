#include "C_KeyboardMovement.hpp"
#include "Object.hpp"

C_KeyboardMovement::C_KeyboardMovement(Object* owner) : Component(owner), moveSpeed(300.f) {}

void C_KeyboardMovement::Awake()
{
    velocity = owner->GetComponent<C_Velocity>();
}

void C_KeyboardMovement::SetInput(Input* input)
{
    this->input = input;
}

void C_KeyboardMovement::SetMovementSpeed(float moveSpeed)
{
    this->moveSpeed = moveSpeed;
}

void C_KeyboardMovement::Update(float deltaTime)
{
    if(input == nullptr)
    {
        return;
    }
    
    float xMove = 0.f;
    if(input->IsKeyPressed(Input::Key::Left))
    {
        xMove = -moveSpeed;
    }
    else if(input->IsKeyPressed(Input::Key::Right))
    {
        xMove = moveSpeed;
    }
    
    float yMove = 0.f;
    if(input->IsKeyPressed(Input::Key::Up))
    {
        yMove = -moveSpeed;
    }
    else if(input->IsKeyPressed(Input::Key::Down))
    {
        yMove = moveSpeed;
    }
    
    velocity->Set(xMove, yMove);
}
