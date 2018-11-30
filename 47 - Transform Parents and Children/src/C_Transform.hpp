#ifndef C_Transform_hpp
#define C_Transform_hpp

#include "Component.hpp"

class C_Transform : public Component
{
public:
    C_Transform(Object* owner);
    
    void LateUpdate(float deltaTime) override;

    void SetPosition(float x, float y);
    void SetPosition(const sf::Vector2f& pos);
    
    void AddPosition(float x, float y);
    void AddPosition(sf::Vector2f pos);
    
    void SetX(float x);
    void SetY(float y);
    
    void AddX(float x);
    void AddY(float y);
    
    sf::Vector2f GetPosition() const;
    const sf::Vector2f& GetPreviousFramePosition() const;
    
    void SetStatic(bool isStatic);
    bool isStatic() const;
    
    void SetParent(std::shared_ptr<C_Transform> parent);
    const std::shared_ptr<C_Transform> GetParent() const;
    
    void AddChild(std::shared_ptr<C_Transform> child);
    void RemoveChild(std::shared_ptr<C_Transform> child);
    const std::vector<std::shared_ptr<C_Transform>>& GetChildren() const;

private:
    sf::Vector2f position;
    sf::Vector2f previousFramePosition;
    bool isStaticTransform;
    std::shared_ptr<C_Transform> parent;
    std::vector<std::shared_ptr<C_Transform>> children;
};

#endif /* C_Transform_hpp */
