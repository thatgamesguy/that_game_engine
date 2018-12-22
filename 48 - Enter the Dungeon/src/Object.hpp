#ifndef Object_hpp
#define Object_hpp

#include <vector>

#include "Window.hpp"
#include "Component.hpp"
#include "C_Transform.hpp"
#include "C_Drawable.hpp"
#include "C_InstanceID.hpp"
#include "SharedContext.hpp"
#include "C_Collidable.hpp"

//TODO: look into replacing object hierarchy with std::function - https://probablydance.com/2012/12/16/the-importance-of-stdfunction/
class Object
{
public:
    Object(SharedContext* context);
    
    void Awake(); // Called when object created. Use to ensure required components are present.
    void Start(); // Called after Awake method. Use to initialise variables.
    
    void Update(float deltaTime);
    void LateUpdate(float deltaTime);
    void Draw(Window& window);
    
    void OnCollisionEnter(std::shared_ptr<C_BoxCollider> other);
    void OnCollisionStay(std::shared_ptr<C_BoxCollider> other);
    void OnCollisionExit(std::shared_ptr<C_BoxCollider> other);
    
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
        
        if (std::dynamic_pointer_cast<C_Collidable>(newComponent))
        {
            collidables.push_back(std::dynamic_pointer_cast<C_Collidable>(newComponent));
        }
        
        return newComponent;
    };
    
    template <typename T> std::shared_ptr<T> GetComponent()
    {
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
        std::vector<std::shared_ptr<T>> matchingComponents;
        for (auto& exisitingComponent : components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                matchingComponents.emplace_back(std::dynamic_pointer_cast<T>(exisitingComponent));
            }
        }
        
        return matchingComponents;
    };
    
    std::shared_ptr<C_Drawable> GetDrawable();
    
    bool IsQueuedForRemoval();
    void QueueForRemoval();
    
    std::shared_ptr<C_Transform> transform;
    std::shared_ptr<C_InstanceID> instanceID;
    
    SharedContext* context;
    
private:
    std::vector<std::shared_ptr<Component>> components;
    std::shared_ptr<C_Drawable> drawable;
    std::vector<std::shared_ptr<C_Collidable>> collidables;
    bool queuedForRemoval;
};


#endif /* Object_hpp */
