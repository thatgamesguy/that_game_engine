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

class C_Animation : public Component
{
public:
    C_Animation(Object* owner);
    
    void Awake() override;
    
    void Update(float deltaTime) override;
    
    void AddAnimation(AnimationState state, std::shared_ptr<Animation> animation);
    void SetAnimationState(AnimationState state);
    const AnimationState& GetAnimationState() const;
    
    void SetAnimationDirection(FacingDirection dir);
    
private:
    std::shared_ptr<C_Sprite> sprite;
    std::map<AnimationState, std::shared_ptr<Animation>> animations;
    std::pair<AnimationState, std::shared_ptr<Animation>> currentAnimation;
};

#endif /* C_Animation_hpp */
