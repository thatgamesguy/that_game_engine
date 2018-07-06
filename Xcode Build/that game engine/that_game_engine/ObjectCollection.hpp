#ifndef ObjectCollection_hpp
#define ObjectCollection_hpp

#include <memory>
#include <vector>

#include "Object.hpp"

class ObjectCollection
{
public:
    void Add(std::shared_ptr<Object> object);
    void Add(std::vector<std::shared_ptr<Object>>& objects);
    
    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw(Window& window);
    
    void ProcessNewObjects();
    void ProcessRemovals();
    
private:
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<Object>> newObjects;
};

#endif /* ObjectCollection_hpp */
