#ifndef C_ProjectileAttack_hpp
#define C_ProjectileAttack_hpp

#include "Component.hpp"
#include "C_Animation.hpp"
#include "Input.hpp"

class C_ProjectileAttack : public Component
{
public:
    C_ProjectileAttack(Object* owner);
    
    void Awake() override;
    
    void Update(float deltaTime) override;
    
    void SetInput(Input* input);
    
private:
    std::shared_ptr<C_Animation> animation;
    Input* input;
};

#endif /* C_ProjectileAttack_hpp */
