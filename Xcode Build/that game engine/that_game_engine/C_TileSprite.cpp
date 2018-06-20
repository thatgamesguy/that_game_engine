#include "C_TileSprite.hpp"
#include "Object.hpp"

C_TileSprite::C_TileSprite(Object* owner) : Component(owner)
{
    
}

void C_TileSprite::SetTextureAllocator(ResourceAllocator<sf::Texture>* allocator)
{
    this->allocator = allocator;
}


void C_TileSprite::Load(int id, int x, int y, int size, int scale, sf::IntRect textureRect)
{
    if(id >= 0)
    {
        std::shared_ptr<sf::Texture> texture = allocator->Get(id);
        sprite.setTexture(*texture);
        sprite.setScale(scale, scale);
        sprite.setTextureRect(textureRect);
    }
    
    this->x = x;
    this->y = y;
    this->size = size;
    this->scale = scale;
}

void C_TileSprite::SetPosition(int x, int y)
{
    sprite.setPosition(x, y);
}

void C_TileSprite::Draw(Window& window)
{
    // Set up culling space
    const sf::FloatRect viewSpace = window.GetViewSpace();
    const sf::Vector2i viewBegin(floor(viewSpace.left / size * scale), floor(viewSpace.top / size * scale));
    const sf::Vector2i viewEnd(ceil((viewSpace.left + viewSpace.width) / size * scale), ceil((viewSpace.top + viewSpace.height) / size * scale));
    
    if(x > viewBegin.x  && x < viewEnd.x  &&
       y > viewBegin.y && y < viewEnd.y)
    {
        window.Draw(sprite);
    }
    else
    {
        int x;
    }
}

