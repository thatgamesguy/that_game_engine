#ifndef C_Sprite_hpp
#define C_Sprite_hpp

#include "Component.hpp"
#include "C_Transform.hpp"
#include "ResourceAllocator.hpp"

class C_Sprite : public Component
{
public:
    C_Sprite(Object* owner);
    
    void SetTextureAllocator(ResourceAllocator<sf::Texture>* allocator);
    
    void Load(int id);
    void Load(const std::string& filePath);
    
    void LateUpdate(float deltaTime) override;
    void Draw(Window& window) override;
    
private:
    ResourceAllocator<sf::Texture>* allocator;
    sf::Sprite sprite;
};

#endif /* C_Sprite_hpp */
