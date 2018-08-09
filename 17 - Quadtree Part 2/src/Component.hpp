#ifndef Component_hpp
#define Component_hpp

#include "Window.hpp"

class Object;

class Component
{
public:
    Component(Object* owner) : owner(owner){}
    
    virtual void Awake() {};
    virtual void Start() {};
    
    virtual void Update(float deltaTime) {};
    virtual void LateUpdate(float deltaTime) {};
    
    Object* owner;
};

#endif /* Component_hpp */
