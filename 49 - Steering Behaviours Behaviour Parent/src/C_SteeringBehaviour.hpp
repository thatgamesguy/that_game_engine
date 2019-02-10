#ifndef C_SteeringBehaviour_hpp
#define C_SteeringBehaviour_hpp

#include "Component.hpp"
#include "C_Tag.hpp"
#include "SharedContext.hpp"
#include "Quadtree.hpp"

class C_SteeringBehaviour : public Component
{
public:
    C_SteeringBehaviour(Object* owner);
    
    virtual const sf::Vector2f GetForce() = 0;
    
    unsigned int GetWeight() const;
    void SetWeight(unsigned int weight);
    
protected:
    Object* GetEntityInSight(float sightRadius, Tag tag) const;
    std::vector<Object*> GetEntitiesInSight(float sightRadius, Tag tag) const;
    
    
private:
    unsigned int weight;
};

#endif /* C_SteeringBehaviour_hpp */
