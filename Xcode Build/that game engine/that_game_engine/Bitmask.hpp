#ifndef Bitmask_hpp
#define Bitmask_hpp

#include <stdint.h>

class Bitmask
{
public:
    Bitmask();
    
    Bitmask(uint32_t bits);
    
    void SetMask(Bitmask& other);
    uint32_t GetMask() const;
    
    bool GetBit(int pos) const;
    void SetBit(int pos, bool on);
    
    void SetBit(int pos);
    void ClearBit(int pos);
    
    void Clear();
    
private:
    uint32_t bits;
};

#endif /* Bitmask_hpp */
