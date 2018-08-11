#ifndef QuadTree_hpp
#define QuadTree_hpp

#include <memory>
#include <vector>

#include "C_BoxCollider.hpp"
#include "Object.hpp"
#include "Debug.hpp"

class Quadtree
{
public:
    Quadtree();
    Quadtree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, Quadtree* parent);
    
    void DrawDebug();
    
    void Insert(std::shared_ptr<C_BoxCollider> object);
    void Remove(std::shared_ptr<C_BoxCollider> object);
    void Clear();
    void UpdatePosition(std::shared_ptr<C_BoxCollider> object);
    
    std::vector<std::shared_ptr<C_BoxCollider>> Search(const sf::FloatRect& area);
   
    const sf::FloatRect& GetBounds() const;
    
private:
    void Search(const sf::FloatRect& area, std::vector<std::shared_ptr<C_BoxCollider>>& overlappingObjects);
    
    int GetChildIndexForObject(const sf::FloatRect& objectBounds);
    void Split();
    
    //TODO: is there a better way to store this data? enum?
    static const int thisTree = -1;
    static const int childNE = 0;
    static const int childNW = 1;
    static const int childSW = 2;
    static const int childSE = 3;
    
    int maxObjects;
    int maxLevels;
    
    Quadtree* parent;
    std::shared_ptr<Quadtree> children[4];
    
    std::vector<std::shared_ptr<C_BoxCollider>> objects; 
    
    int level;
    
    sf::FloatRect bounds;
};

#endif /* QuadTree_hpp */
