#ifndef C_Collidable_hpp
#define C_Collidable_hpp

#include <memory>

class Object;

class C_Collidable
{
public:
    virtual void OnCollisionEnter(Object& owner, std::shared_ptr<Object> other) {};
    virtual void OnCollisionStay(Object& owner, std::shared_ptr<Object> other) {};
    virtual void OnCollisionExit(Object& owner, std::shared_ptr<Object> other) {};
};

#endif /* C_Collidable_hpp */
