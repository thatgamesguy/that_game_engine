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

//TODO: this shares code with GetEntitiesInSight, reduce code copy/paste
Object* C_SteeringBehaviour::GetEntityInSight(float sightRadius, Tag tag) const
{
    const float halfRadius = sightRadius * 0.5f;
    const sf::Vector2f& pos = owner->transform->GetPosition();
    const sf::FloatRect searchRect(pos.x - halfRadius, pos.y - halfRadius, sightRadius, sightRadius);
    
    std::vector<std::shared_ptr<C_BoxCollider>> collisions = owner->context->collisionTree->Search(searchRect);
    
    if(collisions.size() > 0)
    {
        const unsigned int thisID = owner->instanceID->Get();
        
        for (auto c : collisions)
        {
            if(c->owner->instanceID->Get() != thisID)
            {
                if(c->owner->tag->Get() == tag)
                {
                    return c->owner;
                    
                }
            }
        }
    }
    
    return nullptr;
}

std::vector<Object*> C_SteeringBehaviour::GetEntitiesInSight(float sightRadius, Tag tag) const
{
    // needs to retrieve objects in area from quad tree.
    std::vector<Object*> entitiesInSight;
    
    const float halfRadius = sightRadius * 0.5f;
    const sf::Vector2f& pos = owner->transform->GetPosition();
    const sf::FloatRect searchRect(pos.x - halfRadius, pos.y - halfRadius, sightRadius, sightRadius);
    
    //TODO: we want to be able to use a circle as a search area.
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
                    //TODO: we don't want to calculate this for every behaviour every frame. Move to seperate sight component
                    entitiesInSight.push_back(c->owner);

                }
                
            }
        }
    }

    return entitiesInSight;
}


