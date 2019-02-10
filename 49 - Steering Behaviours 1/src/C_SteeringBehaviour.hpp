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
    
    unsigned int GetWeight() const;
    
protected:
    void SetWeight(unsigned int weight);
    std::vector<std::shared_ptr<Object>> GetEntitiesInSight(float sightRadius, Tag tag) const;
    
    
private:
    unsigned int weight;
};

#endif /* C_SteeringBehaviour_hpp */
