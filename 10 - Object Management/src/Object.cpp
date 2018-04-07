#include "Object.hpp"

Object::Object() : queuedForRemoval(false)
{
    transform = AddComponent<C_Transform>();
}

void Object::Awake()
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Awake();
    }
}

void Object::Start()
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Start();
    }
}

void Object::Update(float timeDelta)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Update(timeDelta);
    }
}

void Object::LateUpdate(float timeDelta)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->LateUpdate(timeDelta);
    }
}

void Object::Draw(Window& window)
{
    for(int i = components.size() - 1; i >= 0; i--)
    {
        components[i]->Draw(window);
    }
}

void Object::QueueForRemoval()
{
    queuedForRemoval = true;
}

bool Object::IsQueuedForRemoval()
{
    return  queuedForRemoval;
}
