#ifndef Raycast_hpp
#define Raycast_hpp

#include "Object.hpp"
#include "S_Collidable.hpp"

struct RaycastResult
{
    Object* collision;
};

#endif /* Raycast_hpp */

class Raycast
{
public:
    Raycast(Quadtree& collisions);
    
    RaycastResult Cast(const sf::Vector2f& from, const sf::Vector2f& to);
    
private:
    sf::FloatRect BuildRect(const sf::Vector2f& lineOne, const sf::Vector2f& lineTwo);
    std::vector<sf::Vector2f> BuildLinePoints(const sf::Vector2f& from, const sf::Vector2f& to);
    
    Quadtree& collisions;
};
