#ifndef C_Sprite_hpp
#define C_Sprite_hpp

#include "Component.hpp"
#include "C_Transform.hpp"

class C_Sprite : public Component
{
public:
    C_Sprite(Object* owner);
    
    void Load(const std::string& filePath);
    
    void LateUpdate(float deltaTime) override;
    void Draw(Window& window) override;
    
private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif /* C_Sprite_hpp */
