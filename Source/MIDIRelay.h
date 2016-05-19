/*
  ==============================================================================

    MIDIRelayManager.h
    Created: 12 May 2016 4:48:51pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef MIDIRELAYMANAGER_H_INCLUDED
#define MIDIRELAYMANAGER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include <list>
#include <memory>

#include "Utils.h"
#include "Relay.h"
#include "OSCTargetManager.h"

class MIDIRelay : public Relay
{
public:
    
    MIDIRelay();
    MIDIRelay(std::shared_ptr<OSCTarget> _target, String _group, int _channel);
    
    void setChannel(int _channel);
    int getChannel();
    
    void relay(MidiMessage& message);
    
private:

    int channel;
    
};

class MIDIRelayManager : public ListManager<MIDIRelay>
{
    
};


#endif  // MIDIRELAYMANAGER_H_INCLUDED
