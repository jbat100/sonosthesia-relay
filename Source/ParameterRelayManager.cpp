/*
  ==============================================================================

    ParameterRelayManager.cpp
    Created: 12 May 2016 4:49:08pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "ParameterRelayManager.h"

ParameterRelay::ParameterRelay() : index(-1), target(nullptr), address("")
{
    identifier = Uuid().toString();
}

ParameterRelay::ParameterRelay(int _index, std::shared_ptr<OSCTarget> _target, OSCAddress _address) : index(_index), target(_target), address(_address)
{
    identifier = Uuid().toString();
}

void ParameterRelay::setIndex(int _index)
{
    index = _index;
}

int ParameterRelay::getIndex()
{
    return index;
}

std::shared_ptr<OSCTarget> ParameterRelay::getTarget()
{
    return target;
}

void ParameterRelay::setTarget(std::shared_ptr<OSCTarget> _target)
{
    target = _target;
}

void ParameterRelay::relay(int index, float value)
{
    
}

String ParameterRelay::getIdentifier()
{
    return identifier;
}

std::list< std::shared_ptr<ParameterRelay> > ParameterRelayManager::getRelays()
{
    return relays;
}

std::shared_ptr<ParameterRelay> ParameterRelayManager::newRelay()
{
    std::shared_ptr<ParameterRelay> relay(new ParameterRelay);
    relays.push_back(relay);
    return relay;
}

void ParameterRelayManager::deleteRelay(String identifier)
{
    for (auto i = relays.begin(); i != relays.end();)
    {
        if ((*i)->getIdentifier() == identifier) relays.erase(i);
        else i++;
    }
}

void ParameterRelayManager::clear()
{
    relays.clear();
}
