#include "C_InteractableTalking.hpp"

C_InteractableTalking::C_InteractableTalking(Object* owner) : Component(owner), textToSay("Hi") {}

void C_InteractableTalking::OnInteraction(Object* other)
{
    Debug::Log(textToSay);
    
    std::shared_ptr<Object> labelObj = std::make_shared<Object>(owner->context);
    
    sf::Vector2f pos = owner->transform->GetPosition();
    
    pos.y -= 80;
    
    labelObj->transform->SetPosition(pos);
    
    auto label = labelObj->AddComponent<C_UILabel>();
    label->SetDrawLayer(DrawLayer::UI);
    
    label->SetBackgroundSize(sf::Vector2f(120, 120));
    label->SetBackgroundColour(sf::Color::Black);
    
    label->SetFontColour(sf::Color::Black);
    label->SetText(textToSay);
    
    owner->context->objects->Add(labelObj);
}
