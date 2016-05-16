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


std::list< std::shared_ptr<Relay> > RelayManager::getRelays()
{
    return relays;
}

std::shared_ptr<Relay> RelayManager::newRelay()
{
    std::shared_ptr<Relay> relay(new Relay);
    relays.push_back(relay);
    return relay;
}

void RelayManager::deleteRelay(String identifier)
{
    for (auto i = relays.begin(); i != relays.end();)
    {
        if ((*i)->getIdentifier() == identifier) relays.erase(i);
        else i++;
    }
}

std::shared_ptr<Relay> RelayManager::getRelay(String identifier)
{
    for (auto i = relays.begin(); i != relays.end();)
    {
        if ((*i)->getIdentifier() == identifier) return (*i);
    }
    
    throw std::invalid_argument( "unknown identifier" );
}

void RelayManager::clear()
{
    relays.clear();
}
