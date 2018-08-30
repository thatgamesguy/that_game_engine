#include "Object.hpp"

Object::Object(SharedContext* context) : context(context),  queuedForRemoval(false)
{
    transform = AddComponent<C_Transform>();
    instanceID = AddComponent<C_InstanceID>();
}

void Object::Awake()
{
    for (auto c : components)
    {
        c->Awake();
    }
}

void Object::Start()
{
    for (auto c : components)
    {
        c->Start();
    }
}

void Object::Update(float timeDelta)
{
    for (const auto component : components)
    {
        component->Update(timeDelta);
    }
}

void Object::LateUpdate(float timeDelta)
{
    for (const auto component : components)
    {
        component->LateUpdate(timeDelta);
    }
}

void Object::Draw(Window& window)
{
    drawable->Draw(window);
}

void Object::OnCollisionEnter(std::shared_ptr<C_BoxCollider> other)
{
    for (const auto& component : collidables)
    {
        component->OnCollisionEnter(other);
    }
}

void Object::OnCollisionStay(std::shared_ptr<C_BoxCollider> other)
{
    for (const auto& component : collidables)
    {
        component->OnCollisionStay(other);
    }
}

void Object::OnCollisionExit(std::shared_ptr<C_BoxCollider> other)
{
    for (const auto& component : collidables)
    {
        component->OnCollisionExit(other);
    }
}

void Object::QueueForRemoval()
{
    queuedForRemoval = true;
}

bool Object::IsQueuedForRemoval()
{
    return queuedForRemoval;
}

std::shared_ptr<C_Drawable> Object::GetDrawable()
{
    return drawable;
}
