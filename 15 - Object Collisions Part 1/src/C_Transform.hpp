#ifndef C_Transform_hpp
#define C_Transform_hpp

#include "Component.hpp"

class C_Transform : public Component
{
public:
    C_Transform(Object* owner);

    void SetPosition(float x, float y);
    void SetPosition(const sf::Vector2f& pos);
    
    void AddPosition(float x, float y);
    void AddPosition(sf::Vector2f pos);
    
    void SetX(float x);
    void SetY(float y);
    
    void AddX(float x);
    void AddY(float y);
    
    const sf::Vector2f& GetPosition() const;
    
    void SetStatic(bool isStatic);
    bool isStatic() const;

private:
    sf::Vector2f position;
    bool isStaticTransform;
};

#endif /* C_Transform_hpp */
