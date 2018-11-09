#ifndef C_Direction_hpp
#define C_Direction_hpp

#include "Component.hpp"
#include "Animation.hpp"
#include "C_Velocity.hpp"

class C_Direction : public Component
{
public:
    C_Direction(Object* owner);
    
    void Awake() override;
    
    FacingDirection Get();
    
    sf::Vector2i GetHeading();
    
private:
    std::shared_ptr<C_Velocity> velocity;
    FacingDirection currentDir;
};

#endif /* C_Direction_hpp */
