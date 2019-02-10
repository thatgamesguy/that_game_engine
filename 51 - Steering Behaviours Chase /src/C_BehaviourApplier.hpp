#ifndef C_BehaviourApplier_hpp
#define C_BehaviourApplier_hpp

#include "Component.hpp"
#include "C_SteeringBehaviour.hpp"
#include "C_Velocity.hpp"

class C_BehaviourApplier : public Component
{
public:
    C_BehaviourApplier(Object* owner);
    
    void Awake() override;
    void Update(float deltaTime) override;
    
private:
    inline float SqrMagnitude(const sf::Vector2f& v);
    
    std::vector<std::shared_ptr<C_SteeringBehaviour>> behaviours;
    std::shared_ptr<C_Velocity> velocity;
};


#endif /* C_BehaviourApplier_hpp */
