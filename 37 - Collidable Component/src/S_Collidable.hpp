#ifndef S_Collidable_hpp
#define S_Collidable_hpp

#include <vector>
#include <memory>
#include <set>
#include <unordered_map>

#include "Object.hpp"
#include "Quadtree.hpp"
#include "Bitmask.hpp"
#include "EnumClassHash.hpp"

class S_Collidable
{
public:
    S_Collidable();
    
    void Add(std::vector<std::shared_ptr<Object>>& objects);
    void ProcessRemovals();
    void UpdatePositions(std::vector<std::shared_ptr<Object>>& objects);
    void Resolve();
    
    void Update();
    
private:
    void ProcessCollisions(std::vector<std::shared_ptr<Object>>& first, std::vector<std::shared_ptr<Object>>& second);
    
    std::unordered_map<CollisionLayer, Bitmask, EnumClassHash> collisionLayers;
    std::unordered_map<CollisionLayer, std::vector<std::shared_ptr<C_BoxCollider>>, EnumClassHash> collidables;
    
    
    Quadtree collisionTree;
};



#endif /* S_Collidable_hpp */
