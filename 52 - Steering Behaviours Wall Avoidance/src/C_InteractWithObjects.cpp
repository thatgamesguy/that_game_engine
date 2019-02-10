#include "C_InteractWithObjects.hpp"
#include "Object.hpp"

C_InteractWithObjects::C_InteractWithObjects(Object* owner) : Component(owner), interactionDistance(60.f) {}

void C_InteractWithObjects::Awake()
{
    direction = owner->GetComponent<C_Direction>();
}

void C_InteractWithObjects::Update(float deltaTime)
{
    if (owner->context->input->IsKeyDown(Input::Key::R))
    {
        sf::Vector2i heading = direction->GetHeading();
        
        const sf::Vector2f& startPoint = owner->transform->GetPosition();
        
        sf::Vector2f endPoint;
        
        endPoint.x = startPoint.x + (heading.x * interactionDistance);
        endPoint.y = startPoint.y + (heading.y * interactionDistance);
        
        RaycastResult result = owner->context->raycast->Cast(startPoint, endPoint, owner->instanceID->Get());
        
        if(result.collision != nullptr)
        {
            // Retrieve all interactable components
            auto interactables = result.collision->GetComponents<C_Interactable>();
            
            for (auto& interactable : interactables)
            {
                interactable->OnInteraction(owner);
            }
        }
        
   }
}
