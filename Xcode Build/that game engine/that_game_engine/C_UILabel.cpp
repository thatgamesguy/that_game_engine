#include "C_UILabel.hpp"
#include "Object.hpp"

C_UILabel::C_UILabel(Object* owner) : Component(owner) {}

void C_UILabel::Start()
{
    const int fontID = owner->context->fontAllocator->Add(owner->context->workingDir->Get() + "Joystix Monospace.ttf");
    std::shared_ptr<sf::Font> font = owner->context->fontAllocator->Get(fontID);
    text.setFont(*font);
}

void C_UILabel::Draw(Window& window)
{
    window.Draw(background);
    window.Draw(text);
}

bool C_UILabel::ContinueToDraw() const
{
    return !owner->IsQueuedForRemoval();
}

//TODO: UI elements do not often move so we should not need to query the position every frame
void C_UILabel::LateUpdate(float deltaTime)
{
    sf::Vector2f pos = owner->transform->GetPosition();
    const sf::FloatRect& backBounds = background.getLocalBounds();
    
    const sf::Vector2f centredPosition = sf::Vector2f(pos.x - (backBounds.width * 0.5f), pos.y - (backBounds.height * 0.5f));
    
    background.setPosition(centredPosition);
    text.setPosition(centredPosition);
}

void C_UILabel::SetText(const std::string& text)
{
    this->text.setString(text);
}

void C_UILabel::SetBackgroundSize(const sf::Vector2f& size)
{
    background.setSize(size);
    background.setPosition(text.getPosition());
}

void C_UILabel::SetFontColour(const sf::Color& colour)
{
    text.setFillColor(colour);
    text.setOutlineColor(colour);
}

void C_UILabel::SetBackgroundColour(const sf::Color& colour)
{
    background.setFillColor(colour);
}
