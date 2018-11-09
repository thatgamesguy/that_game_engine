#ifndef C_MovementAnimation_hpp
#define C_MovementAnimation_hpp

#include "Component.hpp"
#include "C_Velocity.hpp"
#include "C_Animation.hpp"

class C_MovementAnimation : public Component
{
public:
    C_MovementAnimation(Object* owner);
    
    void Awake() override;
    
    void Update(float deltaTime) override;
    
private:
    std::shared_ptr<C_Velocity> velocity;
    std::shared_ptr<C_Animation> animation;
};

#endif /* C_MovementAnimation_hpp */
