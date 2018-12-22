#ifndef C_WalkInLine_hpp
#define C_WalkInLine_hpp

#include "Component.hpp"
#include "C_Interactable.hpp"
#include "C_Velocity.hpp"

class C_WalkInLine : public Component, public C_Interactable
{
public:
    C_WalkInLine(Object* owner);
    
    void Awake() override;

    void OnInteraction(Object* other) override;
    
private:
    std::shared_ptr<C_Velocity> velocity;
    float moveSpeed;
};

#endif /* C_WalkInLine_hpp */
