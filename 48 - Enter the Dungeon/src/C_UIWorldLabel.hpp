#ifndef C_UIWorldLabel_hpp
#define C_UIWorldLabel_hpp

#include "Component.hpp"
#include "C_Drawable.hpp"

class C_UIWorldLabel : public Component, public C_Drawable
{
public:
    C_UIWorldLabel(Object* owner);
    
    void Start() override;
    
    void Draw(Window& window) override;
    bool ContinueToDraw() const override;
    
    void LateUpdate(float deltaTime) override;
    
    void SetText(const std::string& text);
    void SetBackgroundSize(const sf::Vector2f& size);
    
    void SetFontColour(const sf::Color& colour);
    void SetBackgroundColour(const sf::Color& colour);
    
private:
    sf::Text text;
    sf::RectangleShape background;
    
};

#endif /* C_UIWorldLabel_hpp */
