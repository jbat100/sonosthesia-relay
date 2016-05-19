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
    ParameterRelay(std::shared_ptr<OSCTarget> _target, String _group, String _descriptor, int _index);
    
    void setIndex(int _index);
    int getIndex();
    
    void setDescriptor(String _descriptor);
    String getDescriptor();
    
    void relay(int index, float value);
    
private:
    
    String descriptor;
    int index;
};

class ParameterRelayManager : public ListManager<ParameterRelay>
{
    
};



#endif  // PARAMETERRELAYMANAGER_H_INCLUDED
