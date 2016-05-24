/*
  ==============================================================================

    MIDIRelayManager.cpp
    Created: 12 May 2016 4:48:51pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "MIDIRelay.h"

MIDIRelay::MIDIRelay() :
    Relay(),
    channel(-1)
{

}

MIDIRelay::MIDIRelay(std::shared_ptr<OSCTarget> _target, String _group, int _channel) :
    Relay(_target, _group),
    channel(_channel)
{

}

MIDIRelay::MIDIRelay(String _identifier, std::shared_ptr<OSCTarget> _target, String _group, int _channel) :
    Relay(_identifier, _target, _group),
    channel(_channel)
{
    
}

void MIDIRelay::setChannel(int _channel)
{
    channel = _channel;
}

int MIDIRelay::getChannel()
{
    return channel;
}

void MIDIRelay::relay(MidiMessage& m)
{
    
    if (channel != m.getChannel() && channel != -1)
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

