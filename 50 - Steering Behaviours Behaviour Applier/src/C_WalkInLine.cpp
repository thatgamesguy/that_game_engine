#include "C_WalkInLine.hpp"
#include "Object.hpp"

C_WalkInLine::C_WalkInLine(Object* owner) : Component(owner), moveSpeed(100.f) {}


void C_WalkInLine::Awake()
{
    velocity = owner->GetComponent<C_Velocity>();
} 

void C_WalkInLine::OnInteraction(Object *other)
{
    velocity->Set(moveSpeed, 0.f);
}

