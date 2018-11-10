#ifndef C_InteractableTalking_hpp
#define C_InteractableTalking_hpp

#include "Component.hpp"
#include "C_Interactable.hpp"
#include "Debug.hpp"
#include "C_UILabel.hpp"
#include "ObjectCollection.hpp"

class C_InteractableTalking : public Component, public C_Interactable
{
public:
    C_InteractableTalking(Object* owner);
    
    void OnInteraction(Object* other) override;
    
private:
    std::string textToSay;
};

#endif /* C_InteractableTalking_hpp */
