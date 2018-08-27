#ifndef C_KeyboardMovement_hpp
#define C_KeyboardMovement_hpp

#include "Component.hpp"
#include "Input.hpp"
#include "C_Velocity.hpp"

class C_KeyboardMovement : public Component
{
public:
    C_KeyboardMovement(Object* owner);
    
    void Awake() override;
    
    void SetInput(Input* input);
    void SetMovementSpeed(float moveSpeed);
    
    void Update(float deltaTime) override;
    
private:
    float moveSpeed;
    Input* input;
    
    // Remove line to animation
    std::shared_ptr<C_Velocity> velocity;
};

#endif /* C_KeyboardMovement_hpp */
