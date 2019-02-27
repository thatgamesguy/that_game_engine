#ifndef Math_hpp
#define Math_hpp

class Mathf
{
public:
    static inline sf::Vector2f Normalise(const sf::Vector2f& v)
    {
        float l = Magnitude(v);
        
        if (l != 0)
        {
            return v / l;
        }
        
        return v;
    }
    
    static inline float Magnitude(const sf::Vector2f& v)
    {
        return sqrt((v.x * v.x) + (v.y * v.y));
    }
};


#endif /* Math_hpp */
