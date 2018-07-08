#include "S_Collidable.hpp"

S_Collidable::S_Collidable()
{
    collisionLayers.insert(std::make_pair(CollisionLayer::Default, Bitmask(0)));
}

void S_Collidable::Add(std::vector<std::shared_ptr<Object>>& objects)
{
    for (auto o : objects)
    {
        auto collider = o->GetComponent<C_Collider>();
        if (collider)
        {
            CollisionLayer layer = collider->GetLayer();
            
            auto itr = collidables.find(layer);
            
            if (itr != collidables.end())
            {
                collidables[layer].push_back(collider);
            }
            else
            {
                std::vector<std::shared_ptr<C_Collider>> objs;
                objs.push_back(collider);
                
                collidables.insert(std::make_pair(layer, objs));
            }
        }
    }
}

void S_Collidable::ProcessRemovals()
{
    for (auto& layer : collidables)
    {
        auto itr = layer.second.begin();
        while (itr != layer.second.end())
        {
            if ((*itr)->IsQueuedForRemoval())
            {
                itr = layer.second.erase(itr);
            }
            else
            {
                ++itr;
            }
        }
    }
}

void S_Collidable::Resolve()
{
    for (auto maps = collidables.begin(); maps != collidables.end(); ++maps)
    {
        for (auto c : maps->second)
        {
            collisionTree.Search(c->)
        }
    }
}

void S_Collidable::ProcessCollisions(std::vector<std::shared_ptr<Object>>& first, std::vector<std::shared_ptr<Object>>& second)
{
    for (auto itr = first.begin(); itr != first.end(); ++itr)
    {
        auto first = (*itr);
        auto collider1 = first->GetComponent<C_Collider>();
        
        for (auto itr2 = second.begin(); itr2 != second.end(); ++itr2)
        {
            auto second = (*itr2);
            
            // Do not need to test collisions between two static objects.
            if(first->m_transform->isStatic() && second->m_transform->isStatic())
            {
                continue;
            }
            
            if (first->m_instanceID->Get() == second->m_instanceID->Get())
            {
                continue;
            }
            
            auto collider2 = (*itr2)->GetComponent<C_Collider2D>();
            
            Manifold m = collider1->Intersects(collider2);
            
            if (m.colliding)
            {
                auto emplace = m_colliding.insert(std::make_pair(first, second));
                
                bool wasEmplaced = emplace.second;
                
                bool firstIsTrigger = collider1->IsTrigger();
                bool secondIsTrigger = collider2->IsTrigger();
                
                //OnCollisionEnter
                if (wasEmplaced)
                {
                    if (firstIsTrigger || secondIsTrigger)
                    {
                        first->OnTriggerEnter(second);
                        second->OnTriggerEnter(first);
                    }
                    else
                    {
                        first->OnCollisionEnter(second);
                        second->OnCollisionEnter(first);
                    }
                }
                
                //Prevent non-trigger colliders from intersecting
                if (!firstIsTrigger && !secondIsTrigger)
                {
                    //TODO: how do we want to handle this? Do we want both to attempt resolution?
                    collider1->ResolveOverlap(m);
                    //m.resolve = -m.resolve;
                    collider2->ResolveOverlap(m);
                }
            }
        }
    }
}




