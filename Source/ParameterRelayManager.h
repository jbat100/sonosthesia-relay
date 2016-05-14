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

#include "OSCTargetManager.h"

class ParameterRelay
{
public:
    
    ParameterRelay();
    ParameterRelay(int _index, std::shared_ptr<OSCTarget> _target, OSCAddress address);
    
    void setIndex(int _index);
    int getIndex();
    
    void setAddress(OSCAddress _address);
    OSCAddress getAddress();
    
    std::shared_ptr<OSCTarget> getTarget();
    void setTarget(std::shared_ptr<OSCTarget> _target);
    
    void relay(int index, float value);
    
    String getIdentifier();
    
private:
    
    String identifier;
    
    int index;
    std::shared_ptr<OSCTarget> target;
    OSCAddress address;
    
};

class ParameterRelayManager
{
public:
    
    std::list< std::shared_ptr<ParameterRelay> > getRelays();
    
    std::shared_ptr<ParameterRelay> newRelay();
    
    void deleteRelay(String identifier);
    
    void clear();
    
private:
    
    std::list< std::shared_ptr<ParameterRelay> > relays;
    
};


#endif  // PARAMETERRELAYMANAGER_H_INCLUDED
