#ifndef Animation_hpp
#define Animation_hpp

#include <vector>
#include <functional>
#include <map>
#include "Bitmask.hpp"

enum class FacingDirection
{
    None,
    Left,
    Right,
    Up,
    Down
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

using AnimationAction = std::function<void(void)>;

class Animation
{
public:
    Animation();
    
    void AddFrame(int textureID, int x, int y, int width, int height, float frameTime);
    
    const FrameData* GetCurrentFrame() const;
    
    bool UpdateFrame(float deltaTime);
    
    void AddFrameAction(unsigned int frame, AnimationAction action);
    
    void Reset();
    
private:
    void IncrementFrame();
    void RunActionForCurrentFrame();
    
    std::vector<FrameData> frames;
    int currentFrameIndex;
    float currentFrameTime;
    bool releaseFirstFrame;
    std::map<int, std::vector<AnimationAction>> actions;
    Bitmask framesWithActions;
    
};


#endif /* Animation_hpp */
