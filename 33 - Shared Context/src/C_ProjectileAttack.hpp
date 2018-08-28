#ifndef C_ProjectileAttack_hpp
#define C_ProjectileAttack_hpp

#include "Component.hpp"
#include "C_Animation.hpp"
#include "ObjectCollection.hpp"

class C_ProjectileAttack : public Component
{
public:
    C_ProjectileAttack(Object* owner);
    
    void Awake() override;
    void Start() override;
    
    void Update(float deltaTime) override;
    
private:
    void SpawnProjectile();
    
    std::shared_ptr<C_Animation> animation;
    int projectileTextureID;
};

#endif /* C_ProjectileAttack_hpp */
