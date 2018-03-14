#include "Object.hpp"

Object::Object()
{
    transform = AddComponent<C_Transform>();
}

void Object::Awake()
{
    for (auto& c : components)
    {
        c->Awake();
    }
}

void Object::Start()
{
    for (auto& c : components)
    {
        c->Start();
    }
}

void Object::Update(float timeDelta)
{
    for (const auto& component : components)
    {
        component->Update(timeDelta);
    }
}

void Object::LateUpdate(float timeDelta)
{
    for (const auto& component : components)
    {
        component->LateUpdate(timeDelta);
    }
}

void Object::Draw(Window& window)
{
    for (const auto& component : components)
    {
        component->Draw(window);
    }
}
