#include "C_InstanceID.hpp"

unsigned int C_InstanceID::count = 0;

C_InstanceID::C_InstanceID(Object* owner) : Component(owner), id(count++){}

C_InstanceID::~C_InstanceID(){}

unsigned int C_InstanceID::Get() const
{
    return id;
}
