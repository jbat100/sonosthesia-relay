/*
  ==============================================================================

    Relay.cpp
    Created: 16 May 2016 4:07:07pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "Relay.h"


Relay::Relay() : target(nullptr)
{
    identifier = Uuid().toString();
}

Relay::Relay(std::shared_ptr<OSCTarget> _target) : target(_target)
{
    identifier = Uuid().toString();
    setTarget(target);
}

std::shared_ptr<OSCTarget> Relay::getTarget()
{
    return target;
}

void Relay::setTarget(std::shared_ptr<OSCTarget> _target)
{
    // if we already have a target then stop listening to notifications
    if (target)
    {
        target->remove(this);
    }
    
    if (_target)
    {
        std::cout << "Relay setTarget : " << _target->getHostName() << ":" << _target->getPortNumber() << "\n";
        _target->checkValidity();
        _target->add(this);
    }
    
    target = _target;
}

String Relay::getIdentifier()
{
    return identifier;
}

void Relay::targetInvalidated (OSCTarget* _target)
{
    if (_target != target.get())
    {
        throw std::runtime_error("unexpected target invalidation callback");
    }
    
    std::cout << "Relay nulling target on invalidation\n";
    
    target = nullptr;
}


