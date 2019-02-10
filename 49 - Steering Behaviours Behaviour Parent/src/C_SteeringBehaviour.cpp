#include "C_SteeringBehaviour.hpp"
#include "Object.hpp"

C_SteeringBehaviour::C_SteeringBehaviour(Object* owner) : Component(owner), weight(1) {}

unsigned int C_SteeringBehaviour::GetWeight() const
{
    return weight;
}

void C_SteeringBehaviour::SetWeight(unsigned int weight)
{
    this->weight = weight;
}


std::vector<Object*> C_SteeringBehaviour::GetEntitiesInSight(float sightRadius, Tag tag) const
{
    std::vector<std::shared_ptr<Object>> entitiesInSight;
    
    // needs to retrieve objects in area from quad tree.
    // check if object is not equal to this one and
    // has correct tag and
    // the distance to the object is equal to or less than the sightRadius.
    
    return entitiesInSight;
}
