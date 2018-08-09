#ifndef C_Collider_hpp
#define C_Collider_hpp

#include<memory>
#include <SFML/Graphics.hpp>

#include "Bitmask.hpp"
#include "Component.hpp"

// enum ints used when defining collision layers
//TODO: implement collision layers.
enum class CollisionLayer
{
    Default = 0
};

struct Manifold
{
    bool colliding = false;
    sf::FloatRect other;
};

class C_Collider : public Component
{
public:
    C_Collider(Object* owner);
    ~C_Collider();
    
    virtual Manifold Intersects(std::shared_ptr<C_Collider> other) = 0;
    virtual void ResolveOverlap(const Manifold& m) = 0;
    
    bool IsTrigger() const;
    void SetTrigger(bool isTrigger);
    
    CollisionLayer GetLayer() const;
    void SetLayer(CollisionLayer layer);
    
private:
    bool isTrigger;
    CollisionLayer layer;
};



#endif /* C_Collider_hpp */
