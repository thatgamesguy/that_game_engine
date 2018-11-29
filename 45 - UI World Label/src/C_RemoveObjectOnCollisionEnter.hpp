#ifndef C_RemoveObjectOnCollisionEnter_hpp
#define C_RemoveObjectOnCollisionEnter_hpp

#include "Component.hpp"
#include "C_Collidable.hpp"

class C_RemoveObjectOnCollisionEnter : public Component, public C_Collidable
{
public:
    C_RemoveObjectOnCollisionEnter(Object* owner);
    
    void OnCollisionEnter(std::shared_ptr<C_BoxCollider> other) override;
};

#endif /* C_RemoveObjectOnCollisionEnter_hpp */
