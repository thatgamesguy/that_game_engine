#ifndef C_Interactable_hpp
#define C_Interactable_hpp

#include "Object.hpp"

class C_Interactable
{
public:
    virtual void OnInteraction(Object* other) = 0;
};

#endif /* C_Interactable_hpp */
