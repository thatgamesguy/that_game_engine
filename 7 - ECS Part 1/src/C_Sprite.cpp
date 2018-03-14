#include "C_Sprite.hpp"

C_Sprite::C_Sprite(Object* owner) : Component(owner) {}

void C_Sprite::Load(const std::string& filePath)
{
    texture.loadFromFile(filePath);
    sprite.setTexture(texture);
}

void C_Sprite::Draw(Window& window)
{
    window.Draw(sprite);
}
