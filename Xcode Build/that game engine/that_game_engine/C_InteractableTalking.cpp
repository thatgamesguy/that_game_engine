#include "C_InteractableTalking.hpp"

C_InteractableTalking::C_InteractableTalking(Object* owner) : Component(owner), textToSay("Hi") {}

void C_InteractableTalking::OnInteraction(Object* other)
{
    Debug::Log(textToSay);
}
