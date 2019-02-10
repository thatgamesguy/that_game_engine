#include "Input.hpp"

void Input::Update()
{
    lastFrameKeys.SetMask(thisFrameKeys);

    thisFrameKeys.SetBit((int)Key::Left,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)));
    
    thisFrameKeys.SetBit((int)Key::Right,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)));
    
    thisFrameKeys.SetBit((int)Key::Up,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)));
  
    thisFrameKeys.SetBit((int)Key::Down,
                         (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)));
  
    thisFrameKeys.SetBit((int)Key::Esc, sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
    
    thisFrameKeys.SetBit((int)Key::LBracket, sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket));
    
    thisFrameKeys.SetBit((int)Key::RBracket, sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket));
    
    thisFrameKeys.SetBit((int)Key::E, sf::Keyboard::isKeyPressed(sf::Keyboard::E));
    
     thisFrameKeys.SetBit((int)Key::R, sf::Keyboard::isKeyPressed(sf::Keyboard::R));
}

bool Input::IsKeyDown(Key keycode)
{
    bool lastFrame = lastFrameKeys.GetBit((int)keycode);
    bool thisFrame = thisFrameKeys.GetBit((int)keycode);
    
    return thisFrame && !lastFrame;
}

bool Input::IsKeyPressed(Key keycode)
{
    return thisFrameKeys.GetBit((int)keycode);
}

bool Input::IsKeyUp(Key keycode)
{
    bool lastFrame = lastFrameKeys.GetBit((int)keycode);
    bool thisFrame = thisFrameKeys.GetBit((int)keycode);
    
    return !thisFrame && lastFrame;
}
