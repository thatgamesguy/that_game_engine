#include "C_Tag.hpp"

C_Tag::C_Tag(Object* owner) : Component(owner),
tag(Tag::Default)
{
}

Tag C_Tag::Get() const
{
    return tag;
}

void C_Tag::Set(Tag tag)
{
    this->tag = tag;
}

bool C_Tag::Compare(std::shared_ptr<C_Tag> other) const
{
    return tag == other->tag;
}

bool C_Tag::Compare(Tag other) const
{
    return tag == other;
}
