#include "C_SteeringBehaviourWallAvoidance.hpp"

C_SteeringBehaviourWallAvoidance::C_SteeringBehaviourWallAvoidance(Object* owner) : C_SteeringBehaviour(owner), lookDistance(800.f) {}

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
    
    const sf::Vector2f& velNorm = Mathf::Normalise(vel);
    
    // Front Ray
    auto frontResult = owner->context->raycast->Cast(pos, pos + (velNorm * lookDistance), CollisionLayer::Tile);
    
    if (frontResult.collision != nullptr)
    {
        //Debug::DrawLine(pos, pos + (velNorm * lookDistance), sf::Color::Red);
        
        const sf::Vector2f normal = Mathf::Normalise(pos - frontResult.point);
        
        float distanceFromWall = 50.f;
        
        sf::Vector2f targetPos = frontResult.point + normal * distanceFromWall;
        
        //sf::Vector2f cross =
        
        Debug::DrawLine(pos, frontResult.point, sf::Color::Red);
    }
    else
    {
        Debug::DrawLine(pos, pos + (velNorm * lookDistance));
    }
    
    return force;
    
    // Convert from radians to degrees
    const float angle = 30.f / 57.2958f;
    const sf::Vector2f to = (velNorm * lookDistance);
    
    // Side Rays
    sf::Vector2f directions[] = {
        sf::Vector2f(
        (to.x * cosf(angle)) - (to.y * sinf(angle)),
        (to.y * cosf(angle)) + (to.x * sinf(angle))),
        sf::Vector2f(
        (to.x * cosf(-angle)) - (to.y * sinf(-angle)),
        (to.y * cosf(-angle)) + (to.x * sinf(-angle)))
    };
    
    for (int i = 0; i < 2; i++)
    {
        auto result = owner->context->raycast->Cast(pos, pos + directions[i], CollisionLayer::Tile);
        
        if (result.collision != nullptr)
        {
            // Collided with a side ray.
            Debug::DrawLine(pos, pos + directions[i], sf::Color::Red);
        }
        else
        {
            Debug::DrawLine(pos, pos + directions[i], sf::Color::Yellow);
        }
    }
    
    return force;
}
