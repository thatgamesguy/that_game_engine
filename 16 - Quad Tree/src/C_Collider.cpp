#include "C_Collider.hpp"

C_Collider::C_Collider() : isTrigger(false), layer(CollisionLayer::Default){}

C_Collider::~C_Collider(){}

bool C_Collider::IsTrigger() const
{
    return isTrigger;
}

void C_Collider::SetTrigger(bool isTrigger)
{
    this->isTrigger = isTrigger;
}

CollisionLayer C_Collider::GetLayer() const
{
    return layer;
}

void C_Collider::SetLayer(CollisionLayer layer)
{
    this->layer = layer;
}
