#ifndef Object_hpp
#define Object_hpp

#include <vector>

#include "Window.hpp"
#include "Component.hpp"
#include "C_Transform.hpp"
#include "C_Drawable.hpp"
#include "C_InstanceID.hpp"

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
        
        //TODO: allow us to add more than one component, implement getcomponents
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
        
        if (std::dynamic_pointer_cast<C_Drawable>(newComponent))
        {
            drawable = std::dynamic_pointer_cast<C_Drawable>(newComponent);
        }
        
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
    
    std::shared_ptr<C_Drawable> GetDrawable();
    
    bool IsQueuedForRemoval();
    void QueueForRemoval();
    
    std::shared_ptr<C_Transform> transform;
    std::shared_ptr<C_InstanceID> instanceID;
    
private:
    std::vector<std::shared_ptr<Component>> components;
    std::shared_ptr<C_Drawable> drawable;
    bool queuedForRemoval;
};


#endif /* Object_hpp */
