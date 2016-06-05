/*
  ==============================================================================

    MIDIRelayManager.cpp
    Created: 12 May 2016 4:48:51pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "MIDIRelay.h"

const int MIDIRelay::allChannels = -2;
const int MIDIRelay::noChannel = -1;

MIDIRelay::MIDIRelay() :
    Relay(),
    channel(noChannel)
{

}

MIDIRelay::MIDIRelay(std::shared_ptr<OSCTarget> _target, String _group, int _channel) :
    Relay(_target, _group),
    channel(_channel)
{

}

MIDIRelay::MIDIRelay(String _identifier, std::shared_ptr<OSCTarget> _target, String _group, int _channel) :
    Relay(_identifier, _target, _group)
{
    setChannel(_channel);
}

void MIDIRelay::setChannel(int _channel)
{
    if ( (_channel == noChannel)    ||
         (_channel == allChannels)  ||
         (_channel > 0 && _channel <= 16)  )
    {
        std::cout << "MIDIRelay setChannel " << _channel << "\n";
        channel = _channel;
    }
    else
    {
        throw std::invalid_argument("unexpected channel");
    }
    
}

int MIDIRelay::getChannel()
{
    return channel;
}

void MIDIRelay::relay(MidiMessage& m)
{
    
    if ( (channel != m.getChannel()) && (channel != allChannels) )
    {
        std::cout << "Relaying ignoring message " << m.getDescription() << "\n";
        return;
    }
    
    if (!getTarget())
    {
        std::cout << "Relay has no target\n";
        return;
    }
    
    OSCAddressPattern pattern = OSCAddressPattern("/" + getGroup() + "/midi/");
    
    if (m.isNoteOn())
    {
        OSCMessage message = OSCMessage(pattern, String("note_on"), (int)m.getChannel(), (int)m.getNoteNumber(), (int)m.getVelocity());
        getTarget()->sendMessage(message);
        
        std::cout << "Relaying MIDI: " << m.getDescription() << "\n";
    }
    else if (m.isNoteOff())
    {
        OSCMessage message = OSCMessage(pattern, String("note_off"), (int)m.getChannel(), (int)m.getNoteNumber(), (int)m.getVelocity());
        getTarget()->sendMessage(message);
        
        std::cout << "Relaying MIDI: " << m.getDescription() << "\n";
    }
}

