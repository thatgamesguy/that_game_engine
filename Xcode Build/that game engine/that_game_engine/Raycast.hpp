#ifndef Raycast_hpp
#define Raycast_hpp

#include "Object.hpp"
#include "S_Collidable.hpp"

struct RaycastResult
{
    Object* collision;
    CollisionLayer layer;
    sf::Vector2f point;
    sf::Vector2f normal;
};

class Raycast
{
public:
    Raycast(Quadtree& collisions);
    
    RaycastResult Cast(const sf::Vector2f& from, const sf::Vector2f& to, int exclusionID = -1);
    RaycastResult Cast(const sf::Vector2f& from, const sf::Vector2f& to, CollisionLayer layer);
    
private:
    sf::FloatRect BuildRect(const sf::Vector2f& lineOne, const sf::Vector2f& lineTwo);
    std::vector<sf::Vector2f> BuildLinePoints(const sf::Vector2f& from, const sf::Vector2f& to);
    
    Quadtree& collisions;
};

#endif /* Raycast_hpp */
