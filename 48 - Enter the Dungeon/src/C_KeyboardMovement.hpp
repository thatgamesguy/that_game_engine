#ifndef C_KeyboardMovement_hpp
#define C_KeyboardMovement_hpp

#include "Component.hpp"
#include "Input.hpp"
#include "C_Animation.hpp"
#include "C_Velocity.hpp"

class C_KeyboardMovement : public Component
{
public:
    C_KeyboardMovement(Object* owner);
    
    void Awake() override;
    
    void SetMovementSpeed(float moveSpeed);
    
    void Update(float deltaTime) override;
    
private:
    float moveSpeed;
    
    std::shared_ptr<C_Animation> animation;
    std::shared_ptr<C_Velocity> velocity;
};

#endif /* C_KeyboardMovement_hpp */
