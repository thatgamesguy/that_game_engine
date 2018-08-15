#ifndef C_BoxCollider_hpp
#define C_BoxCollider_hpp

#include <math.h>

#include "Component.hpp"
#include "C_Collider.hpp"

enum class Origin { TopLeft, AbsCentre, MidBottom };

class C_BoxCollider : public C_Collider
{
public:
    C_BoxCollider(Object* owner);
    ~C_BoxCollider();
    
    Manifold Intersects(std::shared_ptr<C_Collider> other) override;
    void ResolveOverlap(const Manifold& m) override;
    
    void SetCollidable(const sf::FloatRect& rect);
    const sf::FloatRect& GetCollidable();
    
    void SetOrigin(const Origin& origin);
    
private:
    void SetPosition();
    
private:
    sf::FloatRect AABB;
    Origin origin;
    sf::Vector2f offset;
};

#endif /* C_BoxCollider_hpp */
