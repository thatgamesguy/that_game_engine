#ifndef C_Sprite_hpp
#define C_Sprite_hpp

#include "Component.hpp"

class C_Sprite : public Component
{
public:
    C_Sprite(Object* owner);
    
    void Load(const std::string& filePath);
    
    void Draw(Window& window) override;
    
private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif /* C_Sprite_hpp */
