#ifndef C_Velocity_hpp
#define C_Velocity_hpp

#include <math.h>
#include "Component.hpp"

class C_Velocity : public Component
{
public:
    C_Velocity(Object* owner);
    
    void Update(float deltaTime) override;
    
    void Set(const sf::Vector2f& vel);
    void Set(float x, float y);
    const sf::Vector2f& Get() const;
    
private:
    void ClampVelocity();
    
    sf::Vector2f velocity;
    sf::Vector2f maxVelocity;
};

#endif /* C_Velocity_hpp */
