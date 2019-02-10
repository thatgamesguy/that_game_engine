#ifndef C_SteeringBehaviourWallAvoidance_hpp
#define C_SteeringBehaviourWallAvoidance_hpp

#include "C_SteeringBehaviour.hpp"
#include "Raycast.hpp"
#include "C_Velocity.hpp"

class C_SteeringBehaviourWallAvoidance : public C_SteeringBehaviour
{
public:
    C_SteeringBehaviourWallAvoidance(Object* owner);
    
    void Awake() override;
    
    const sf::Vector2f GetForce() override;
    
private:
    std::shared_ptr<C_Velocity> velocity;
    float lookDistance;
};


#endif /* C_SteeringBehaviourWallAvoidance_hpp */
