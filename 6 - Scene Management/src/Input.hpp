#ifndef Input_hpp
#define Input_hpp

#include <SFML/Graphics.hpp>
#include "Bitmask.hpp"

class Input
{
public:
    enum class KEY
    {
        LEFT = 1,
        RIGHT = 2,
        UP = 3,
        DOWN = 4,
        ESC = 5
    };
    
    void Update();
    
    bool IsKeyPressed(KEY keycode); // Returns true if the key is pressed.
    bool IsKeyDown(KEY keycode); // Returns true if the key was just pressed.
    bool IsKeyUp(KEY keycode); // Returns true if the key was just released.
    
private:
    Bitmask thisFrameKeys;
    Bitmask lastFrameKeys;
};

#endif /* Input_hpp */
