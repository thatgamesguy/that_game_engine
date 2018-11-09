#include "Raycast.hpp"

Raycast::Raycast(Quadtree& collisions) : collisions(collisions) {}

//TODO: using int rather than unsigned int as exclusion id will cause problems if large number of entities.
RaycastResult Raycast::Cast(const sf::Vector2f& from, const sf::Vector2f& to, int exclusionID)
{
    // Build empty raycast result
    RaycastResult result;
    result.collision = nullptr;
    
    // Check if from and to are the same, if true return empty result
    if(from == to)
    {
        return result;
    }
    
    // Create sf::rect that encompasses line
    sf::FloatRect collisionArea = BuildRect(from, to);
    
    Debug::DrawRect(collisionArea, sf::Color::Red);
    
    // Retrieve entities from collision system within the raycast area
    std::vector<std::shared_ptr<C_BoxCollider>> entities = collisions.Search(collisionArea);
    
    // If there are no eneities in the zone return empty result
    if(entities.size() == 0)
    {
        return result;
    }
    
    // Create a stepped line from first to second point
    std::vector<sf::Vector2f> linePoints = BuildLinePoints(from, to);
    
    // for each point in the line check if it intersects with every entity
    for (auto& p : linePoints)
    {
        for (auto& e : entities)
        {
            // Check if entity has been excluded from raycast collision
            if(exclusionID == e->owner->instanceID->Get())
            {
                continue;
            }
            
            sf::FloatRect entityRect = e->GetCollidable();
            if(entityRect.contains(p))
            {
                result.collision = e->owner;
                return result;
            }
        }
    }
    
    return result;
}

sf::FloatRect Raycast::BuildRect(const sf::Vector2f& lineOne, const sf::Vector2f& lineTwo)
{
    const float rectWidth = 0.2f;
    const float halfWidth = rectWidth * 0.5f;
    
    float left, top, width, height;
    
    if(lineOne.x == lineTwo.x) // Vertical line
    {
        left = lineOne.x - halfWidth;
        top = (lineOne.y < lineTwo.y) ? lineOne.y : lineTwo.y;
        width = rectWidth;
        height = fabsf(lineOne.y - lineTwo.y);
    }
    else
    {
        left = (lineOne.x < lineTwo.x) ? lineOne.x : lineTwo.x;
        top = lineOne.y + halfWidth;
        width = fabsf(lineOne.x - lineTwo.x);
        height = rectWidth;
    }
   
    return sf::FloatRect(left, top, width, height);
}

//TODO: Look into Bresenham’s Line genration.
std::vector<sf::Vector2f> Raycast::BuildLinePoints(const sf::Vector2f& from, const sf::Vector2f& to)
{
    // TODO: it would be preferable to calculate in
    // advance the size of "result" and to use a fixed-size array
    // instead of a list.
    std::vector<sf::Vector2f> result;
    
    sf::Vector2f diff = to - from;
    int steps = 0;
    
    float absDiffX = abs(diff.x);
    float absDiffY = abs(diff.y);
    
    if (absDiffX > absDiffY)
    {
        steps = absDiffX;
    }
    else
    {
        steps = absDiffY;
    }
    
    float xStep = diff.x / (float)steps;
    float yStep = diff.y / (float)steps;
    
    float newX = from.x;
    float newY = from.y;
    
    for (int i = 0; i <= steps; i++)
    {
        result.push_back(sf::Vector2f(newX, newY));
        
        newX += xStep;
        newY += yStep;
    }
    
    return result;
}
