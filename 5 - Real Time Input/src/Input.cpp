#include "Input.hpp"

void Input::Update()
{
    lastFrameKeys.SetMask(thisFrameKeys);

    thisFrameKeys.SetBit((int)KEY::LEFT,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)));
    
    thisFrameKeys.SetBit((int)KEY::RIGHT,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)));
    
    thisFrameKeys.SetBit((int)KEY::UP,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)));
  
    thisFrameKeys.SetBit((int)KEY::DOWN,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)));
  
    thisFrameKeys.SetBit((int)KEY::ESC), sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
}

bool Input::IsKeyDown(KEY keycode)
{
    if (!IsKeyPressed(keycode))
    {
        return false;
    }
    
    return !lastFrameKeys.GetBit((int)keycode);
}

bool Input::IsKeyPressed(KEY keycode)
{
    return thisFrameKeys.GetBit((int)keycode);
}

bool Input::IsKeyUp(KEY keycode)
{
    if (IsKeyPressed(keycode))
    {
        return false;
    }
    
    return lastFrameKeys.GetBit((int) keycode);
}
