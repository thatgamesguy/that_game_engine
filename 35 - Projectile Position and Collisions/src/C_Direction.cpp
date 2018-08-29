#include "C_Direction.hpp"
#include "Object.hpp"

C_Direction::C_Direction(Object* owner) : Component(owner), currentDir(FacingDirection::Down) { }

void C_Direction::Awake()
{
    velocity = owner->GetComponent<C_Velocity>();
}

FacingDirection C_Direction::Get() 
{
    const sf::Vector2f& currentVel = velocity->Get();
    
    if(currentVel.x != 0.f || currentVel.y != 0.f)
    {
        float velXAbs = fabs(currentVel.x);
        float velYAbs = fabs(currentVel.y);
        
        if(velXAbs > velYAbs)
        {
            if(currentVel.x < 0)
            {
                currentDir = FacingDirection::Left;
            }
            else
            {
                currentDir = FacingDirection::Right;
            }
        }
        else
        {
            if(currentVel.y < 0)
            {
                currentDir = FacingDirection::Up;
            }
            else
            {
                currentDir = FacingDirection::Down;
            }
        }
    }
    
    return currentDir;
}
