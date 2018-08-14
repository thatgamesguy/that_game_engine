#ifndef C_Animation_hpp
#define C_Animation_hpp

#include "Component.hpp"
#include "Animation.hpp"
#include "C_Sprite.hpp"

enum class AnimationState
{
    None,
    Idle,
    Walk
};

using AnimationList = std::map<FacingDirection, std::shared_ptr<Animation>>;

class C_Animation : public Component
{
public:
    C_Animation(Object* owner);
    
    void Awake() override;
    
    void Update(float deltaTime) override;
    
    void AddAnimation(AnimationState state, AnimationList& animationList);
   
    void SetAnimationState(AnimationState state);
    const AnimationState& GetAnimationState() const;
    
    void SetAnimationDirection(FacingDirection dir);
    
private:
    std::shared_ptr<C_Sprite> sprite;
    std::map<AnimationState, AnimationList> animations;
    std::pair<AnimationState, std::shared_ptr<Animation>> currentAnimation;
    FacingDirection currentDirection;
};

#endif /* C_Animation_hpp */
