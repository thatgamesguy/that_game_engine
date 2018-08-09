#include "Quadtree.hpp"

Quadtree::Quadtree() : Quadtree(5, 5, 0, {0, 0, 1920, 1080}, nullptr){}

Quadtree::Quadtree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, Quadtree* parent) : maxObjects(maxObjects), maxLevels(maxLevels), level(level), bounds(bounds), parent(parent){}

void Quadtree::Insert(std::shared_ptr<C_BoxCollider> object)
{
    if(!bounds.intersects(object->GetCollidable()))
    {
        return;
    }
    
    if(children[0] != nullptr)
    {
        int indexToPlaceObject = GetChildIndexForObject(object->GetCollidable());
        
        if(indexToPlaceObject != thisTree)
        {
            children[indexToPlaceObject]->Insert(object);
            return;
        }
    }
    
    objects.emplace_back(object);
    
    if(objects.size() > maxObjects && level < maxLevels && children[0] == nullptr)
    {
        Split();
        
        auto objIterator = objects.begin();
        while (objIterator != objects.end())
        {
            auto obj = *objIterator;
            int indexToPlaceObject = GetChildIndexForObject(obj->GetCollidable());
            
            if (indexToPlaceObject != thisTree)
            {
                children[indexToPlaceObject]->Insert(obj);
                objIterator = objects.erase(objIterator);
                
            }
            else
            {
                ++objIterator;
            }
        }
    }
}

void Quadtree::Remove(std::shared_ptr<C_BoxCollider> object)
{
    int index = GetChildIndexForObject(object->GetCollidable());
    
    if(index == thisTree || children[index] == nullptr)
    {
        for(int i = 0; i < objects.size(); i++)
        {
            if(objects.at(i)->owner->instanceID->Get() == object->owner->instanceID->Get())
            {
                objects.erase(objects.begin() + i);
                break;
            }
        }
    }
    else
    {
        return children[index]->Remove(object);
    }
}

void Quadtree::Clear()
{
    objects.clear();
    
    for(int i = 0; i < 4; i++)
    {
        if(children[i] != nullptr)
        {
            children[i]->Clear();
            children[i] = nullptr;
        }
    }
}
