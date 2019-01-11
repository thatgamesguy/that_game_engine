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


std::vector<std::shared_ptr<Object>> C_SteeringBehaviour::GetEntitiesInSight(float sightRadius, Tag tag) const
{
    // needs to retrieve objects in area from quad tree.
    
    std::vector<std::shared_ptr<Object>> entitiesInSight;
    
    const float halfRadius = sightRadius * 0.5f;
    const sf::Vector2f& pos = owner->transform->GetPosition();
    const sf::FloatRect searchRect(pos.x - halfRadius, pos.y - halfRadius, sightRadius, sightRadius);
    std::vector<std::shared_ptr<C_BoxCollider>> collisions = owner->context->collisionTree->Search(searchRect);
    
    if(collisions.size() > 0)
    {
        const unsigned int thisID = owner->instanceID->Get();
        
        for (auto c : collisions)
        {
            // check if object is not qual to this one
            if(c->owner->instanceID->Get() != thisID)
            {
                // has correct tag
                if(c->owner->tag->Get() == tag)
                {
                    // the distance to the object is equal to or less than the sightRadius.
                    
                    
                    entitiesInSight.push_back(c->owner);
                    need to make staic so every behaviour is not maintaining own list
                }
                
            }
        }
    }

    return entitiesInSight;
}
