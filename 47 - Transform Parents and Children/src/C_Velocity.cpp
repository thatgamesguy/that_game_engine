#include "C_Velocity.hpp"
#include "Object.hpp"

C_Velocity::C_Velocity(Object* owner) : Component(owner), maxVelocity(500.f, 500.f) { }

void C_Velocity::Update(float deltaTime)
{
    owner->transform->AddPosition(velocity * deltaTime);
}

void C_Velocity::Set(const sf::Vector2f& vel)
{
    velocity = vel;
    
    ClampVelocity();
}

void C_Velocity::Set(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
    
    ClampVelocity();
}

const sf::Vector2f& C_Velocity::Get() const
{
    return velocity;
}

void C_Velocity::ClampVelocity()
{
    if (fabs(velocity.x) > maxVelocity.x)
    {
        if (velocity.x > 0.f)
        {
            velocity.x = maxVelocity.x;
        }
        else
        {
            velocity.x = -maxVelocity.x;
        }
    }
    
    if (fabs(velocity.y) > maxVelocity.y)
    {
        if (velocity.y > 0.f)
        {
            velocity.y = maxVelocity.y;
        }
        else
        {
            velocity.y = -maxVelocity.y;
        }
    }
}
