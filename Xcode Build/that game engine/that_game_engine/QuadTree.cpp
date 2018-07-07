#include "QuadTree.hpp"

QuadTree::QuadTree() : QuadTree(10, 5, 0, {0.f, 0.f, defaultWidth, defaultHeight}, nullptr){}

QuadTree::QuadTree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, QuadTree* parent)
{
    
}

void QuadTree::Insert(std::shared_ptr<C_BoxCollider> object)
{
    if(children[0] != nullptr)
    {
        int indexToPlaceObject = GetChildIndexRectangleBelongsIn(object->GetCollidable());
        
        if(indexToPlaceObject != thisTree)
        {
            children[indexToPlaceObject]->Insert(object);
            return;
        }
    }
    
    objects.emplace_back(object);
    
    if(objects.size() > maxObjects && level < maxLevels)
    {
        Split();
        
        int i = 0;
        while (i < objects.size())
        {
            int indexToPlaceObject = GetChildIndexRectangleBelongsIn(objects.at(i)->GetCollidable());
            
            if (indexToPlaceObject != thisTree)
            {
                children[indexToPlaceObject]->Insert(objects.at(i));
                objects.erase(objects.begin() + i);
            }
            else
            {
                i++;
            }
        }
    }
}

void QuadTree::Remove(std::shared_ptr<C_BoxCollider> object)
{
    int index = GetChildIndexRectangleBelongsIn(object->GetCollidable());
    
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

void QuadTree::Clear()
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

std::vector<std::shared_ptr<C_BoxCollider>> QuadTree::Search(const sf::FloatRect& area)
{
    std::vector<std::shared_ptr<C_BoxCollider>> returnList;
    
    std::vector<std::shared_ptr<C_BoxCollider>> possibleOverlaps = Search(std::vector<std::shared_ptr<C_BoxCollider>>(), area);
    
    for (auto collider : possibleOverlaps)
    {
        if (area.intersects(collider->GetCollidable()))
        {
            returnList.emplace_back(collider);
        }
    }

    return returnList;     
}

std::vector<std::shared_ptr<C_BoxCollider>> QuadTree::Search(std::vector<std::shared_ptr<C_BoxCollider>> overlappingObjects, const sf::FloatRect& area)
{
    overlappingObjects.insert(overlappingObjects.end(), objects.begin(), objects.end());
    
    int index = GetChildIndexRectangleBelongsIn(area);
    
    if(index == thisTree || children[0] == nullptr)
    {
        if(children[0] != nullptr)
        {
            for(int i = 0; i < 4; i++)
            {
                if(children[i]->GetBounds().intersects(area))
                {
                    children[i]->Search(overlappingObjects, area);
                }
            }
        }
    }
    else if(children[index] != nullptr)
    {
        children[index]->Search(overlappingObjects, area);
    }
    
    return overlappingObjects;
}

const sf::FloatRect& QuadTree::GetBounds() const
{
    return bounds;
}

int QuadTree::GetChildIndexRectangleBelongsIn(const sf::FloatRect& objectBounds)
{
    int index = -1;
    double verticalDividingLine = bounds.left + bounds.width * 0.5f;
    double horizontalDividingLine = bounds.top + bounds.height * 0.5f;
    
    bool fitsCompletelyInNorthHalf = objectBounds.top < horizontalDividingLine && (objectBounds.height + objectBounds.top < horizontalDividingLine);
    bool fitsCompletelyInSouthHalf = objectBounds.top > horizontalDividingLine;
    bool fitsCompletelyInWestHalf = objectBounds.left < verticalDividingLine && (objectBounds.left + objectBounds.width < verticalDividingLine);
    bool fitsCompletelyInEastHalf = objectBounds.left > verticalDividingLine;
    
    if(fitsCompletelyInEastHalf)
    {
        if(fitsCompletelyInNorthHalf)
        {
            index = childNE;
        }
        else if(fitsCompletelyInSouthHalf)
        {
            index = childSE;
        }
    }
    else if(fitsCompletelyInWestHalf)
    {
        if(fitsCompletelyInNorthHalf)
        {
            index = childNW;
        }
        else if(fitsCompletelyInSouthHalf)
        {
            index = childSW;
        }
    }
    return index;
}

void QuadTree::Split()
{
    int childWidth = bounds.width / 2;
    int childHeight = bounds.height / 2;
    
    children[childNE] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left + childWidth, bounds.top, childWidth, childHeight), this);
    children[childNW] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left, bounds.top, childWidth, childHeight), this);
    children[childSW] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left, bounds.top + childHeight, childWidth, childHeight), this);
    children[childSE] = std::make_shared<QuadTree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left + childWidth, bounds.top + childHeight, childWidth, childHeight), this);
}


