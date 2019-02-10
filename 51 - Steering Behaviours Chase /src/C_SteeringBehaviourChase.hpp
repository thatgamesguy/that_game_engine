#ifndef C_SteeringBehaviourChase_hpp
#define C_SteeringBehaviourChase_hpp

#include "C_SteeringBehaviour.hpp"

class C_SteeringBehaviourChase : public C_SteeringBehaviour
{
public:
    C_SteeringBehaviourChase(Object* owner);
    
    const sf::Vector2f GetForce() override;
    
    void SetTarget(Tag tag);
    void SetSightRadius(float radius);
    void SetChaseSpeed(float speed);
    
private:
    //TODO: move to separate class.
    inline sf::Vector2f Normalise(const sf::Vector2f& v)
    {
        float l = Magnitude(v);
        
        if (l != 0)
        {
            return v / l;
        }
        
        return v;
    }
    
    //TODO: move to separate class.
    inline float Magnitude(const sf::Vector2f& v)
    {
        return sqrt((v.x * v.x) + (v.y * v.y));
    }
    
    float sightRadius;
    float chaseSpeed;
    Tag targetTag;
};

#endif /* C_SteeringBehaviourChase_hpp */
