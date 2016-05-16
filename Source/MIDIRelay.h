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

#include "Relay.h"
#include "OSCTargetManager.h"

class MIDIRelay : public Relay
{
public:
    
    MIDIRelay();
    MIDIRelay(int _channel, std::shared_ptr<OSCTarget> _target);
    
    void setChannel(int _channel);
    int getChannel();
    
    void relay(MidiMessage& message);
    
private:

    int channel;
    
};


#endif  // MIDIRELAYMANAGER_H_INCLUDED
