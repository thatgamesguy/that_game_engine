#ifndef C_KeyboardMovement_hpp
#define C_KeyboardMovement_hpp

#include "Component.hpp"
#include "Input.hpp"
#include "C_Animation.hpp"

class C_KeyboardMovement : public Component
{
public:
    C_KeyboardMovement(Object* owner);
    
    void Awake() override;
    
    void SetInput(Input* input);
    void SetMovementSpeed(int moveSpeed);
    
    void Update(float deltaTime) override;
    
private:
    int moveSpeed;
    Input* input;
    
    std::shared_ptr<C_Animation> animation;
};

#endif /* C_KeyboardMovement_hpp */
