#ifndef C_ProjectileAttack_hpp
#define C_ProjectileAttack_hpp

#include <unordered_map>

#include "Component.hpp"
#include "C_Animation.hpp"
#include "ObjectCollection.hpp"
#include "EnumClassHash.hpp"
#include "C_RemoveObjectOnCollisionEnter.hpp"

class C_ProjectileAttack : public Component
{
public:
    C_ProjectileAttack(Object* owner);
    
    void Awake() override;
    void Start() override;
    
    void Update(float deltaTime) override;
    
private:
    void SpawnProjectile();
    
    static std::unordered_map<FacingDirection, sf::IntRect, EnumClassHash> textureDirectionBindings;
    static std::unordered_map<FacingDirection, sf::Vector2f, EnumClassHash> offsetDirectionBindings;
    static std::unordered_map<FacingDirection, sf::Vector2f, EnumClassHash> velocityDirectionBindings;
    
    std::shared_ptr<C_Animation> animation;
    std::shared_ptr<C_Direction> direction;
    int projectileTextureID;
    float projectileVelocity;
};

#endif /* C_ProjectileAttack_hpp */
