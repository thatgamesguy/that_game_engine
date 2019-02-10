#include "C_SteeringBehaviourWallAvoidance.hpp"

C_SteeringBehaviourWallAvoidance::C_SteeringBehaviourWallAvoidance(Object* owner) : C_SteeringBehaviour(owner), lookDistance(100.f) {}

void C_SteeringBehaviourWallAvoidance::Awake()
{
    velocity = owner->GetComponent<C_Velocity>();
}

const sf::Vector2f C_SteeringBehaviourWallAvoidance::GetForce()
{
    sf::Vector2f force(0, 0);
    
    const sf::Vector2f& pos = owner->transform->GetPosition();
    const sf::Vector2f& vel = velocity->Get();
    
    if(vel.x == 0 && vel.y == 0)
    {
        return force;
    }
    
    const sf::Vector2f& velNorm = Normalise(vel);
    
    
    // Raycast in front to detect wall
    auto result = owner->context->raycast->Cast(pos, pos + (velNorm * lookDistance), owner->instanceID->Get());
    
    if (result.collision != nullptr)
    {
        // Draw red line if colliding with any object
        Debug::DrawLine(pos, pos + (velNorm * lookDistance), sf::Color::Red);
    }
    else
    {
        // Otherwise draw white line
        Debug::DrawLine(pos, pos + (velNorm * lookDistance));
    }
    
    return force;
}
