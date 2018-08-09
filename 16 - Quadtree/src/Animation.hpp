#ifndef Animation_hpp
#define Animation_hpp

#include <vector>

enum class FacingDirection
{
    None,
    Left,
    Right
};

struct FrameData
{
    int id;
    int x;
    int y;
    int width;
    int height;
    float displayTimeSeconds;
};

class Animation
{
public:
    Animation(FacingDirection direction);
    
    void AddFrame(int textureID, int x, int y, int width, int height, float frameTime);
    
    const FrameData* GetCurrentFrame() const;
    
    bool UpdateFrame(float deltaTime);
    
    void Reset();
    
    void SetDirection(FacingDirection dir);
    
    FacingDirection GetDirection() const;
    
private:
    void IncrementFrame();
    
    std::vector<FrameData> frames;
    int currentFrameIndex;
    float currentFrameTime;
    FacingDirection direction;
};


#endif /* Animation_hpp */
