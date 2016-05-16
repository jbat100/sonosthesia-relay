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
}

std::shared_ptr<OSCTarget> Relay::getTarget()
{
    return target;
}

void Relay::setTarget(std::shared_ptr<OSCTarget> _target)
{
    target = _target;
}

String Relay::getIdentifier()
{
    return identifier;
}


