#include "C_Collider.hpp"

C_Collider::C_Collider(Object* owner) : Component(owner), layer(CollisionLayer::Default){}

C_Collider::~C_Collider(){}

CollisionLayer C_Collider::GetLayer() const
{
    return layer;
}

void C_Collider::SetLayer(CollisionLayer layer)
{
    this->layer = layer;
}
