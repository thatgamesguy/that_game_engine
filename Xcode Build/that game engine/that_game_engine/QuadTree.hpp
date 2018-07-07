#ifndef QuadTree_hpp
#define QuadTree_hpp

#include <memory>
#include <vector>

#include "C_BoxCollider.hpp"
#include "Object.hpp"

class QuadTree
{
public:
    QuadTree();
    QuadTree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, QuadTree* parent);
    
    void Insert(std::shared_ptr<C_BoxCollider> object);
    void Remove(std::shared_ptr<C_BoxCollider> object);
    void Clear();
    
    std::vector<std::shared_ptr<C_BoxCollider>> Search(const sf::FloatRect& area);
    std::vector<std::shared_ptr<C_BoxCollider>> Search(std::vector<std::shared_ptr<C_BoxCollider>> overlappingObjects, const sf::FloatRect& area);
    
    const sf::FloatRect& GetBounds() const;
    
private:
    int GetChildIndexRectangleBelongsIn(const sf::FloatRect& objectBounds);
    void Split();
    
    static const int thisTree = -1;
    static const int childNE = 0;
    static const int childNW = 1;
    static const int childSW = 2;
    static const int childSE = 3;
    
    int maxObjects;
    int maxLevels;
    float defaultWidth;
    float defaultHeight;
    
    QuadTree* parent;
    std::shared_ptr<QuadTree> children[4];
    
    std::vector<std::shared_ptr<C_BoxCollider>> objects; 
    
    int level;
    
    sf::FloatRect bounds;
    
};

#endif /* QuadTree_hpp */
