#include "C_RemoveObjectOnCollisionEnter.hpp"
#include "Object.hpp"

C_RemoveObjectOnCollisionEnter::C_RemoveObjectOnCollisionEnter(Object* owner) : Component(owner) {}

void C_RemoveObjectOnCollisionEnter::OnCollisionEnter(std::shared_ptr<C_BoxCollider> other)
{
    owner->QueueForRemoval();
}
