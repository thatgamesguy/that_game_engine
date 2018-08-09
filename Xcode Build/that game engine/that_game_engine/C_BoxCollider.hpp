#ifndef C_BoxCollider_hpp
#define C_BoxCollider_hpp

#include <math.h>

#include "Component.hpp"
#include "C_Collider.hpp"

class C_BoxCollider : public C_Collider
{
public:
    C_BoxCollider(Object* owner);
    ~C_BoxCollider();
    
    Manifold Intersects(std::shared_ptr<C_Collider> other) override;
    void ResolveOverlap(const Manifold& m) override;
    
    void SetCollidable(const sf::FloatRect& rect);
    const sf::FloatRect& GetCollidable();
    
    sf::FloatRect GetPreviousFrameCollidable() const;
    
    void SetOffset(const sf::Vector2f& offset);
    void SetOffset(float x, float y);
    
    void SetSize(const sf::Vector2f& size);
    void SetSize(float width, float height);
    
private:
    void SetPosition();
    
    sf::FloatRect AABB;
    sf::Vector2f offset;
};

#endif /* C_BoxCollider_hpp */
