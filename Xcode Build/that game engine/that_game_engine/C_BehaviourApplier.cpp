#include "C_BehaviourApplier.hpp"
#include "Object.hpp"

C_BehaviourApplier::C_BehaviourApplier(Object* owner) : Component(owner)
{
}

void C_BehaviourApplier::Awake()
{
    behaviours = owner->GetComponents<C_SteeringBehaviour>();
    velocity = owner->GetComponent<C_Velocity>();
}

void C_BehaviourApplier::Update(float deltaTime)
{
    sf::Vector2f force(0.f, 0.f);
    
    for (const auto& b : behaviours)
    {
        force += b->GetForce() * (float)b->GetWeight();
    }
    
    velocity->Set(force);
}

//TODO: if needed by any other class, move to own 'Math' class.
inline float C_BehaviourApplier::SqrMagnitude(const sf::Vector2f& v)
{
    return v.x*v.x + v.y*v.y;
}

