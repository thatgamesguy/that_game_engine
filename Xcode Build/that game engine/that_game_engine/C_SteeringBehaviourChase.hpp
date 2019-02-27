#ifndef C_SteeringBehaviourChase_hpp
#define C_SteeringBehaviourChase_hpp

#include "C_SteeringBehaviour.hpp"
#include "Math.hpp"

class C_SteeringBehaviourChase : public C_SteeringBehaviour
{
public:
    C_SteeringBehaviourChase(Object* owner);
    
    const sf::Vector2f GetForce() override;
    
    void SetTarget(Tag tag);
    void SetSightRadius(float radius);
    void SetChaseSpeed(float speed);
    
private:    
    float sightRadius;
    float chaseSpeed;
    Tag targetTag;
};

#endif /* C_SteeringBehaviourChase_hpp */
