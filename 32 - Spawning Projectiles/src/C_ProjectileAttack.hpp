#ifndef C_ProjectileAttack_hpp
#define C_ProjectileAttack_hpp

#include "Component.hpp"
#include "C_Animation.hpp"
#include "Input.hpp"
#include "ObjectCollection.hpp"
#include "WorkingDirectory.hpp"

class C_ProjectileAttack : public Component
{
public:
    C_ProjectileAttack(Object* owner);
    
    void Awake() override;
    
    void Start() override;
    
    void Update(float deltaTime) override;
    
    void SetInput(Input* input);
    void SetObjectCollection(ObjectCollection* objects);
    void SetWorkingDirectory(WorkingDirectory* workingDirectory);
    void SetTextureAllocator(ResourceAllocator<sf::Texture>* textureAllocator);
    
private:
    void SpawnProjectile();
    
    std::shared_ptr<C_Animation> animation;
    Input* input;
    ObjectCollection* objects;
    WorkingDirectory* workingDirectory;
    ResourceAllocator<sf::Texture>* textureAllocator;
    int projectileTextureID;
};

#endif /* C_ProjectileAttack_hpp */
