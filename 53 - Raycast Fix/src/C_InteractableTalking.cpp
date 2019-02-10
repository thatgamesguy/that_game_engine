#include "C_InteractableTalking.hpp"

C_InteractableTalking::C_InteractableTalking(Object* owner) : Component(owner), textToSay("Bye!") {}

void C_InteractableTalking::OnInteraction(Object* other)
{
    std::shared_ptr<Object> labelObj = std::make_shared<Object>(owner->context);
    
    auto label = labelObj->AddComponent<C_UIWorldLabel>();
    label->SetDrawLayer(DrawLayer::UI);
    
    label->SetBackgroundSize(sf::Vector2f(120, 120));
    label->SetBackgroundColour(sf::Color::Black);
    
    label->SetFontColour(sf::Color::White);
    label->SetText(textToSay);
    
    labelObj->transform->SetParent(owner->transform);
    labelObj->transform->SetPosition(0.f, -80.f);
    
    owner->context->objects->Add(labelObj);
}
