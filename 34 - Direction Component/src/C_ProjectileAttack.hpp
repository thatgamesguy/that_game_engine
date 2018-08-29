#ifndef C_ProjectileAttack_hpp
#define C_ProjectileAttack_hpp

#include <unordered_map>

#include "Component.hpp"
#include "C_Animation.hpp"
#include "ObjectCollection.hpp"

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

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
    
    std::shared_ptr<C_Animation> animation;
    std::shared_ptr<C_Direction> direction;
    int projectileTextureID;
};

#endif /* C_ProjectileAttack_hpp */
