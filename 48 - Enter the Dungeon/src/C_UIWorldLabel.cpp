#include "C_UIWorldLabel.hpp"
#include "Object.hpp"

C_UIWorldLabel::C_UIWorldLabel(Object* owner) : Component(owner) {}

void C_UIWorldLabel::Start()
{
    const int fontID = owner->context->fontAllocator->Add(owner->context->workingDir->Get() + "Joystix Monospace.ttf");
    std::shared_ptr<sf::Font> font = owner->context->fontAllocator->Get(fontID);
    text.setFont(*font);
}

void C_UIWorldLabel::Draw(Window& window)
{
    window.Draw(background);
    window.Draw(text);
}

bool C_UIWorldLabel::ContinueToDraw() const
{
    return !owner->IsQueuedForRemoval();
}

//TODO: UI elements do not often move so we should not need to query the position every frame
void C_UIWorldLabel::LateUpdate(float deltaTime)
{
    sf::Vector2f pos = owner->transform->GetPosition();
    const sf::FloatRect& backBounds = background.getLocalBounds();
    const sf::Vector2f centeredPosition = sf::Vector2f(pos.x - (backBounds.width * 0.5f), pos.y - (backBounds.height * 0.5f));
    
    background.setPosition(centeredPosition);
    text.setPosition(centeredPosition);
}

void C_UIWorldLabel::SetText(const std::string& text)
{
    this->text.setString(text);
}

void C_UIWorldLabel::SetBackgroundSize(const sf::Vector2f& size)
{
    background.setSize(size);
}

void C_UIWorldLabel::SetFontColour(const sf::Color& colour)
{
    text.setFillColor(colour);
    text.setOutlineColor(colour);
}

void C_UIWorldLabel::SetBackgroundColour(const sf::Color& colour)
{
    background.setFillColor(colour);
}
