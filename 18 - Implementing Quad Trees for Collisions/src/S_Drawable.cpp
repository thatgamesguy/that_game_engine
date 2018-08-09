#include "S_Drawable.hpp"

void S_Drawable::Add(std::vector<std::shared_ptr<Object>>& objects)
{
    for (auto o : objects)
    {
        Add(o);
    }
    
    Sort();
}

void S_Drawable::ProcessRemovals()
{
    auto objIterator = drawables.begin();
    while (objIterator != drawables.end())
    {
        auto obj = *objIterator;
        
        if (obj->IsQueuedForRemoval())
        {
            objIterator = drawables.erase(objIterator);
        }
        else
        {
            ++objIterator;
        }
    }
}

void S_Drawable::Add(std::shared_ptr<Object> object)
{
    std::shared_ptr<C_Drawable> draw = object->GetDrawable();
    
    if (draw)
    {
        drawables.emplace_back(object);
    }
}

void S_Drawable::Sort()
{
    std::sort(drawables.begin(), drawables.end(), [](std::shared_ptr<Object> a, std::shared_ptr<Object> b) -> bool
              {
                  return a->GetDrawable()->GetSortOrder() < b->GetDrawable()->GetSortOrder();
              });
}

void S_Drawable::Draw(Window& window)
{
    for (auto& d : drawables)
    {
        d->Draw(window);
    }
}
