#ifndef Object_hpp
#define Object_hpp

#include <vector>
#include <memory>

#include "Window.hpp"
#include "Component.hpp"

class Object
{
public:
    void Awake(); // Called when object created. Use to ensure required components are present.
    void Start(); // Called after Awake method. Use to initialise variables.
    
    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw(Window& window);
    
    template <typename T> std::shared_ptr<T> AddComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        
        // Check that we don't already have a component of this type.
        for (auto& exisitingComponent : components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                return std::dynamic_pointer_cast<T>(exisitingComponent);
            }
        }
        
        std::shared_ptr<T> newComponent = std::make_shared<T>(this);
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
    
private:
    std::vector<std::shared_ptr<Component>> components;
};


#endif /* Object_hpp */
