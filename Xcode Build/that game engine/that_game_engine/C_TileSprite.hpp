#ifndef C_TileCulling_hpp
#define C_TileCulling_hpp

#include <math.h>

#include "Component.hpp"
#include "C_Sprite.hpp"

class C_TileSprite : public Component
{
public:
    C_TileSprite(Object* owner);
    
    void SetTextureAllocator(ResourceAllocator<sf::Texture>* allocator);
    
    void Load(int id, int x, int y, int size, int scale, sf::IntRect textureRect);
    
    void Draw(Window& window) override;
    
    void SetPosition(int x, int y);
    
private:
    ResourceAllocator<sf::Texture>* allocator;
    sf::Sprite sprite;
    int x;
    int y;
    int size;
    int scale;
};

#endif /* C_TileCulling_hpp */
