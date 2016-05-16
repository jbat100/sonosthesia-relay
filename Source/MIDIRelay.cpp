/*
  ==============================================================================

    MIDIRelayManager.cpp
    Created: 12 May 2016 4:48:51pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "MIDIRelay.h"

MIDIRelay::MIDIRelay() : Relay(nullptr), channel(-1) {}

MIDIRelay::MIDIRelay(int _channel, std::shared_ptr<OSCTarget> _target) : Relay(_target), channel(_channel) {}
    
void MIDIRelay::setChannel(int _channel)
{
    channel = _channel;
}

int MIDIRelay::getChannel()
{
    return channel;
}

void MIDIRelay::relay(MidiMessage& message)
{
    
}

