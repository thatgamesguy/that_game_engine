#include "Raycast.hpp"

Raycast::Raycast(Quadtree& collisions) : collisions(collisions) {}

//TODO: using int rather than unsigned int as exclusion id will cause problems if large number of entities.
RaycastResult Raycast::Cast(const sf::Vector2f& from, const sf::Vector2f& to, int exclusionID)
{
    // Build empty raycast result
    RaycastResult result;
    result.collision = nullptr;
    result.layer = CollisionLayer::Default;
    result.point = sf::Vector2f();
    
    // Check if from and to are the same, if true return empty result
    if(from == to)
    {
        return result;
    }
    
    // Create sf::rect that encompasses line
    sf::FloatRect collisionArea = BuildRect(from, to);
    
    //Debug::DrawRect(collisionArea, sf::Color::Red);
    
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
                result.layer = e->GetLayer();
                result.point = p;
                return result;
            }
        }
    }
    
    return result;
}

//TODO: this uses much of the code from the other Cast function, can we simplify?
RaycastResult Raycast::Cast(const sf::Vector2f& from, const sf::Vector2f& to, CollisionLayer layer)
{
    RaycastResult result;
    result.collision = nullptr;
    result.layer = CollisionLayer::Default;
    result.point = sf::Vector2f();
    
    if(from == to)
    {
        return result;
    }
    
    sf::FloatRect collisionArea = BuildRect(from, to);
    
    std::vector<std::shared_ptr<C_BoxCollider>> entities = collisions.Search(collisionArea);
    
    Debug::DrawRect(collisionArea, sf::Color::Red);
    
    if(entities.size() == 0)
    {
        return result;
    }
    
    sf::Vector2f rayDir = to - from;
    rayDir.x = 1.f / rayDir.x;
    rayDir.y = 1.f / rayDir.y;
    
    //std::vector<sf::Vector2f> linePoints = BuildLinePoints(from, to);
    
    //for (auto& p : linePoints)
    //{
    for (auto& e : entities)
    {
        sf::FloatRect entityRect1 = e->GetCollidable();
        Debug::DrawRect(entityRect1, sf::Color::Red);
        
        // If its not on the collision layer we're not interested
        if(e->GetLayer() != layer)
        {
            continue;
        }
        
        sf::FloatRect entityRect = e->GetCollidable();
        const sf::Vector2f topLeft = sf::Vector2f(entityRect.left, entityRect.top);
        const sf::Vector2f bottomRight = sf::Vector2f(entityRect.left + entityRect.width, entityRect.top + entityRect.height);
        
        
        
        //https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms/18459#18459
        
        float t1 = (bottomRight.x - from.x) * rayDir.x;
        float t2 = (topLeft.x - from.x) * rayDir.x;
        float t3 = (bottomRight.y - from.y) * rayDir.y;
        float t4 = (topLeft.y - from.y) * rayDir.y;
        
        float tmin = std::max(std::min(t1, t2), std::min(t3, t4));
        float tmax = std::min(std::max(t1, t2), std::max(t3, t4));
        
        float t;
        // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
        if (tmax < 0)
        {
            //printf("Behind");
            t = tmax;
            //   return false;
        }
        // if tmin > tmax, ray doesn't intersect AABB
        else if (tmin > tmax)
        {
            // printf("no intersection");
            t = tmax;
            // return false;
        }
        else
        {
            t = tmin;
            
            result.collision = e->owner;
            result.layer = e->GetLayer();
            result.point = {tmin, tmax};
//            HOW DO WE CALCULATE POINT?
//            HPW DO WE CALCULATE WHICH SHAPE WAS HIT FIRST?
            //result.point = sf::Vector2f(to.x * t, to.y * t);
            
             if (t == t1) printf("right");
             else if (t == t2) printf("left");
             else if (t == t3) printf("bottom");
             else if (t == t4) printf("top");
        }

    }
    
    return result;
}

sf::FloatRect Raycast::BuildRect(const sf::Vector2f& lineOne, const sf::Vector2f& lineTwo)
{
    float left = (lineOne.x < lineTwo.x) ? lineOne.x : lineTwo.x;
    float top = (lineOne.y < lineTwo.y) ? lineOne.y : lineTwo.y;
    float width = fabs(lineOne.x - lineTwo.x);
    float height = fabs(lineOne.y - lineTwo.y);
    
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
