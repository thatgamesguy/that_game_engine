#include "C_Camera.hpp"
#include "Object.hpp"

C_Camera::C_Camera(Object* owner) : Component(owner)
{
}


void C_Camera::LateUpdate(float deltaTime)
{
    if(window)
    {
        sf::View view = window->GetView();
        
        const sf::Vector2f& playerPos = owner->transform->GetPosition();
        //TODO: remove hard-coding of y value
        view.setCenter(playerPos.x, 500);
        
        window->SetView(view);
    }
}

void C_Camera::SetWindow(Window* gameWindow)
{
    window = gameWindow;
}
