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

//TODO: Create a static map with direction as key and heading as value
sf::Vector2i C_Direction::GetHeading()
{
    FacingDirection direction = Get();
    
    sf::Vector2i heading;
    
    if(direction == FacingDirection::Right)
    {
        heading.x = 1;
    }
    else if (direction == FacingDirection::Left)
    {
        heading.x = -1;
    }
    else if (direction == FacingDirection::Up)
    {
        heading.y = -1;
    }
    else if (direction == FacingDirection::Down)
    {
        heading.y = 1;
    }

    return heading;
}
