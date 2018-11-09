#include "C_InteractWithObjects.hpp"
#include "Object.hpp"

C_InteractWithObjects::C_InteractWithObjects(Object* owner) : Component(owner), interactionDistance(10.f) {}

void C_InteractWithObjects::Awake()
{
    direction = owner->GetComponent<C_Direction>();
}

void C_InteractWithObjects::Update(float deltaTime)
{
    if (owner->context->input->IsKeyDown(Input::Key::R))
    {
        // Raycast to find first object in facing direction.
        
        // Get Direction.
        sf::Vector2i heading = direction->GetHeading();
        
        const sf::Vector2f& startPoint = owner->transform->GetPosition();
        
        sf::Vector2f endPoint;
        
        endPoint.x = heading.x * interactionDistance;
        endPoint.y = heading.y * interactionDistance;
        
        RaycastResult result = owner->context->raycast->Cast(startPoint, endPoint);
        
        if(result.collision)
        {
            // We've got an object to interact with.
            std::cout<< result.collision->instanceID->Get() << std::endl;
        }
        
    }
}
