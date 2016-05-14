/*
  ==============================================================================

    MIDIRelayManager.cpp
    Created: 12 May 2016 4:48:51pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "MIDIRelayManager.h"

MIDIRelay::MIDIRelay() : channel(-1), target(nullptr)
{
    identifier = Uuid().toString();
}

MIDIRelay::MIDIRelay(int _channel, std::shared_ptr<OSCTarget> _target) : channel(_channel), target(_target)
{
    identifier = Uuid().toString();
}
    
void MIDIRelay::setChannel(int _channel)
{
    channel = _channel;
}

int MIDIRelay::getChannel()
{
    return channel;
}

std::shared_ptr<OSCTarget> MIDIRelay::getTarget()
{
    return target;
}

void MIDIRelay::setTarget(std::shared_ptr<OSCTarget> _target)
{
    target = _target;
}

void MIDIRelay::relay(MidiMessage& message)
{
    
}

String MIDIRelay::getIdentifier()
{
    return identifier;
}

std::list< std::shared_ptr<MIDIRelay> > MIDIRelayManager::getRelays()
{
    return relays;
}

std::shared_ptr<MIDIRelay> MIDIRelayManager::newRelay()
{
    std::shared_ptr<MIDIRelay> relay(new MIDIRelay);
    relays.push_back(relay);
    return relay;
}

void MIDIRelayManager::deleteRelay(String identifier)
{
    for (auto i = relays.begin(); i != relays.end();)
    {
        if ((*i)->getIdentifier() == identifier) relays.erase(i);
        else i++;
    }
}

void MIDIRelayManager::clear()
{
    relays.clear();
}
