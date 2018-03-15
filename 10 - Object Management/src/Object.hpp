#ifndef Object_hpp
#define Object_hpp

#include <vector>

#include "Window.hpp"
#include "Component.hpp"
#include "C_Transform.hpp"

class Object
{
public:
    Object();
    
    void Awake(); // Called when object created. Use to ensure required components are present.
    void Start(); // Called after Awake method. Use to initialise variables.
    
    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw(Window& window);
    
    template <typename T> std::shared_ptr<T> AddComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        
        std::shared_ptr<T> newComponent = std::make_shared<T>(this);
        
        // Check that we don't already have a component of this type.
        for (auto& exisitingComponent : components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                return std::dynamic_pointer_cast<T>(exisitingComponent);
            }
        }
        
        components.push_back(newComponent);
        
        return newComponent;
    };
    
    template <typename T> std::shared_ptr<T> GetComponent()
    {
        // Check that we don't already have a component of this type.
        for (auto& exisitingComponent : components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                return std::dynamic_pointer_cast<T>(exisitingComponent);
            }
        }
        
        return nullptr;
    };
    
    template <typename T> std::vector<std::shared_ptr<T>> GetComponents()
    {
        std::vector<std::shared_ptr<T>> components;
        
        for (auto& exisitingComponent : components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                components.push_back(std::dynamic_pointer_cast<T>(exisitingComponent));
            }
        }
        
        return components;
    };
    
    bool IsQueuedForRemoval();
    void QueueForRemoval();
    
    std::shared_ptr<C_Transform> transform;
    
private:
    std::vector<std::shared_ptr<Component>> components;
    bool queuedForRemoval;
};


#endif /* Object_hpp */
