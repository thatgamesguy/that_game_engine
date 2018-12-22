#ifndef C_Animation_hpp
#define C_Animation_hpp

#include <unordered_map>

#include "Component.hpp"
#include "Animation.hpp"
#include "C_Sprite.hpp"
#include "C_Direction.hpp"
#include "EnumClassHash.hpp"

enum class AnimationState
{
    None,
    Idle,
    Walk,
    Projectile
};

using AnimationList = std::unordered_map<FacingDirection, std::shared_ptr<Animation>, EnumClassHash>;

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
    
    void AddAnimationAction(AnimationState state, FacingDirection dir, int frame, AnimationAction action);
    
private:
    std::shared_ptr<C_Sprite> sprite;
    std::unordered_map<AnimationState, AnimationList, EnumClassHash> animations;
    std::pair<AnimationState, std::shared_ptr<Animation>> currentAnimation;
    FacingDirection currentDirection;
    std::shared_ptr<C_Direction> direction;
};

#endif /* C_Animation_hpp */
