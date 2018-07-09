#include "S_Collidable.hpp"

S_Collidable::S_Collidable() 
{
    Bitmask defaultCollisions;
    defaultCollisions.SetBit((int)CollisionLayer::Default);
    collisionLayers.insert(std::make_pair(CollisionLayer::Default, defaultCollisions));
    
    collisionLayers.insert(std::make_pair(CollisionLayer::Tile, Bitmask(0)));
    
    Bitmask playerCollisions;
    playerCollisions.SetBit((int) CollisionLayer::Default);
    playerCollisions.SetBit((int) CollisionLayer::Tile);
    collisionLayers.insert(std::make_pair(CollisionLayer::Player, playerCollisions));
}

void S_Collidable::Add(std::vector<std::shared_ptr<Object>>& objects)
{
    for (auto o : objects)
    {
        auto collider = o->GetComponent<C_BoxCollider>();
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
                std::vector<std::shared_ptr<C_BoxCollider>> objs;
                objs.push_back(collider);
                
                collidables.insert(std::make_pair(layer, objs));
            }
            
            collisionTree.Insert(collider);
        }
    }
}

void S_Collidable::ProcessRemovals()
{
    for (auto layer : collidables)
    {
        auto itr = layer.second.begin();
        while (itr != layer.second.end())
        {
            if ((*itr)->owner->IsQueuedForRemoval())
            {
                collisionTree.Remove(*itr);
                itr = layer.second.erase(itr);
            }
            else
            {
                ++itr;
            }
        }
    }
}

void S_Collidable::Update()
{
    collisionTree.Clear();
    for (auto maps = collidables.begin(); maps != collidables.end(); ++maps)
    {
        for (auto collidable : maps->second)
        {
            collisionTree.Insert(collidable);
        }
    }
    
    Resolve();
}

void S_Collidable::Resolve()
{
    for (auto maps = collidables.begin(); maps != collidables.end(); ++maps)
    {
        for (auto collidable : maps->second)
        {
            if (!collidable->owner->transform->isStatic() && collisionLayers[collidable->GetLayer()].GetMask() != 0)
            {
                std::vector<std::shared_ptr<C_BoxCollider>> collisions = collisionTree.Search(collidable->GetCollidable());
                
                for (auto collision : collisions)
                {
                    if (collidable->owner->instanceID->Get() == collision->owner->instanceID->Get())
                    {
                        continue;
                    }
                                        
                    bool layersCollide = collisionLayers[collidable->GetLayer()].GetBit(((int)collision->GetLayer()));
                    
                    if(layersCollide)
                    {
                        Manifold m = collidable->Intersects(collision);
                        
                        if(m.colliding)
                        {
                            if(collision->owner->transform->isStatic())
                            {
                                collidable->ResolveOverlap(m);
                            }
                            else
                            {
                                
                                //TODO: how shall we handle collisions when both objects are not static?
                                collidable->ResolveOverlap(m);
                            }
                    
                        }
                    }
                }
            }
        }
    }
}






