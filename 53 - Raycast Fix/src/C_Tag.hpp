#ifndef C_Tag_hpp
#define C_Tag_hpp

#include "Component.hpp"

enum class Tag
{
    Default,
    Player,
    NPC
};

class C_Tag : public Component
{
public:
    C_Tag(Object* owner);
    
    Tag Get() const;
    void Set(Tag tag);
    
    bool Compare(std::shared_ptr<C_Tag> other) const;
    bool Compare(Tag other) const;
    
private:
    Tag tag;
};


#endif /* C_Tag_hpp */
