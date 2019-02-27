#include "C_SteeringBehaviourChase.hpp"

C_SteeringBehaviourChase::C_SteeringBehaviourChase(Object* owner) : C_SteeringBehaviour(owner), targetTag(Tag::Default), sightRadius(2000.f), chaseSpeed(100.f) {}

const sf::Vector2f C_SteeringBehaviourChase::GetForce()
{
    sf::Vector2f force(0, 0);
    
    Object* target = GetEntityInSight(sightRadius, targetTag);
    
    if(target != nullptr)
    {
        const sf::Vector2f& pos = owner->transform->GetPosition();
        const sf::Vector2f& targetPos = target->transform->GetPosition();
        
        const sf::Vector2f toTarget = targetPos - pos;
     
        force = Mathf::Normalise(toTarget) * chaseSpeed;
    }
    
    return force;
}

void C_SteeringBehaviourChase::SetSightRadius(float radius)
{
    sightRadius = radius;
}

void C_SteeringBehaviourChase::SetChaseSpeed(float speed)
{
    chaseSpeed = speed;
}

void C_SteeringBehaviourChase::SetTarget(Tag tag)
{
    targetTag = tag;
}
