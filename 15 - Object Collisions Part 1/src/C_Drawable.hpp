
#ifndef C_Drawable_hpp
#define C_Drawable_hpp

#include <SFML/Graphics.hpp>

#include "Window.hpp"

class C_Drawable
{
public:
    C_Drawable();
    virtual ~C_Drawable();
    
    virtual void Draw(Window& window) = 0;
    
    void SetSortOrder(int order);
    int GetSortOrder() const;
    
private:
    int sortOrder;
};



#endif /* C_Drawable_hpp */
