
#ifndef C_Drawable_hpp
#define C_Drawable_hpp

#include <SFML/Graphics.hpp>

#include "Window.hpp"


enum class DrawLayer
{
    Default,
    Background,
    Foreground,
    Entities
};

class C_Drawable
{
public:
    C_Drawable();
    virtual ~C_Drawable();
    
    virtual void Draw(Window& window) = 0;
    virtual bool ContinueToDraw() const = 0;
    
    void SetSortOrder(int order);
    int GetSortOrder() const;
    
    void SetDrawLayer(DrawLayer drawLayer);
    DrawLayer GetDrawLayer() const;
    
private:
    int sortOrder;
    DrawLayer layer;
};



#endif /* C_Drawable_hpp */
