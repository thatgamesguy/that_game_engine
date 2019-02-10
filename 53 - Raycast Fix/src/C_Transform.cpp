#include "C_Transform.hpp"
#include "Object.hpp"

C_Transform::C_Transform(Object* owner) : Component(owner), position(0.f, 0.f), isStaticTransform(false), previousFramePosition(0.f, 0.f) { }

void C_Transform::LateUpdate(float deltaTime)
{
    previousFramePosition = position;
}

void C_Transform::SetPosition(float x, float y)
{
    position.x = x;
    position.y = y;
}

void C_Transform::SetPosition(const sf::Vector2f& pos) { position = pos; }

void C_Transform::AddPosition(float x, float y)
{
    position.x += x;
    position.y += y;
}

void C_Transform::AddPosition(sf::Vector2f pos) { position += pos; }

void C_Transform::SetX(float x) { position.x = x; }

void C_Transform::SetY(float y) { position.y = y; }

void C_Transform::AddX(float x) { position.x += x; }

void C_Transform::AddY(float y) { position.y += y; }

sf::Vector2f C_Transform::GetPosition() const
{
    return (parent == nullptr) ? position : parent->GetPosition() + position;
}

const sf::Vector2f& C_Transform::GetPreviousFramePosition() const { return previousFramePosition; }

void C_Transform::SetStatic(bool isStatic) { isStaticTransform = isStatic; }

bool C_Transform::isStatic() const { return isStaticTransform; }

void C_Transform::SetParent(std::shared_ptr<C_Transform> parent)
{
    this->parent = parent;
    
    this->parent->AddChild(owner->transform);
}

const std::shared_ptr<C_Transform> C_Transform::GetParent() const
{
    return parent;
}

void C_Transform::AddChild(std::shared_ptr<C_Transform> child)
{
    children.push_back(child);
}

void C_Transform::RemoveChild(std::shared_ptr<C_Transform> child)
{
    auto objIterator = children.begin();
    while (objIterator != children.end())
    {
        auto obj = **objIterator;
        
        if (obj.owner->instanceID->Get() == child->owner->instanceID->Get())
        {
            objIterator = children.erase(objIterator);
            break;
        }
        else
        {
            ++objIterator;
        }
    }
}

const std::vector<std::shared_ptr<C_Transform>>& C_Transform::GetChildren() const
{
    return children;
}
