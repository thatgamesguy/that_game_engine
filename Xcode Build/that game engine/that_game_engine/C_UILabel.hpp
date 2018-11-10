#ifndef C_UILabel_hpp
#define C_UILabel_hpp

#include "Component.hpp"
#include "C_Drawable.hpp"

class C_UILabel : public Component, public C_Drawable
{
public:
    C_UILabel(Object* owner);
    
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

#endif /* C_UILabel_hpp */
