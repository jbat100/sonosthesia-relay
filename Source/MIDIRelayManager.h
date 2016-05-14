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

#include "OSCTargetManager.h"

class MIDIRelay
{
public:
    
    MIDIRelay();
    MIDIRelay(int _channel, std::shared_ptr<OSCTarget> _target);
    
    void setChannel(int _channel);
    int getChannel();
    
    std::shared_ptr<OSCTarget> getTarget();
    void setTarget(std::shared_ptr<OSCTarget> _target);
    
    void relay(MidiMessage& message);
    
    String getIdentifier();
    
private:

    int channel;
    String identifier;
    std::shared_ptr<OSCTarget> target;
    
};

class MIDIRelayManager
{
public:
    
    std::list< std::shared_ptr<MIDIRelay> > getRelays();
    
    std::shared_ptr<MIDIRelay> newRelay();
    
    void deleteRelay(String identifier);
    
    void clear();
    
private:
    
    std::list< std::shared_ptr<MIDIRelay> > relays;
    
};


#endif  // MIDIRELAYMANAGER_H_INCLUDED
