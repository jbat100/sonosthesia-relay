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
    
    static const int noIndex;
    
    ParameterRelay();
    ParameterRelay(std::shared_ptr<OSCTarget> _target, String _group, String _descriptor, int _index);
    
    void setIndex(int _index);
    int getIndex();
    
    void setDescriptor(String _descriptor);
    String getDescriptor();
    
    void relay(int index, float value);
    
    void resend();
    
    // overrides for resends
    
    virtual void setTarget(std::shared_ptr<OSCTarget> _target) override;
    virtual void setGroup(String _group) override;
    
private:
    
    void send(float value);
    
    String descriptor;
    int index;
    float lastValue;
    
    static const float noValue;
    static const float threshold;
    
};

class ParameterRelayManager : public ListManager<ParameterRelay>
{
public:
    
    ParameterRelayManager(AudioProcessor& processor);
    
    void refresh();
    
private:
    
    AudioProcessor& processor;
};



#endif  // PARAMETERRELAYMANAGER_H_INCLUDED
