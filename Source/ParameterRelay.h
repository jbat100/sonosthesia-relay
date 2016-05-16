/*
  ==============================================================================

    ParameterRelayManager.h
    Created: 12 May 2016 4:49:08pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef PARAMETERRELAYMANAGER_H_INCLUDED
#define PARAMETERRELAYMANAGER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include <list>
#include <memory>

#include "Relay.h"
#include "OSCTargetManager.h"

class ParameterRelay : public Relay
{
public:
    
    ParameterRelay();
    ParameterRelay(int _index, std::shared_ptr<OSCTarget> _target, OSCAddress address);
    
    void setIndex(int _index);
    int getIndex();
    
    void setAddress(OSCAddress _address);
    OSCAddress getAddress();
    
    void relay(int index, float value);
    
private:
    
    int index;
    OSCAddress address;
    
};

class ParameterRelayManager : public ListManager<ParameterRelay>
{
    
};



#endif  // PARAMETERRELAYMANAGER_H_INCLUDED
