/*
  ==============================================================================

    Relay.h
    Created: 16 May 2016 4:07:07pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef RELAY_H_INCLUDED
#define RELAY_H_INCLUDED

#include <list>
#include <memory>

#include "OSCTargetManager.h"

class Relay : public OSCTargetListener
{
public:
    
    Relay();
    Relay(std::shared_ptr<OSCTarget> _target);
    
    std::shared_ptr<OSCTarget> getTarget();
    void setTarget(std::shared_ptr<OSCTarget> _target);
    
    String getIdentifier();
    
    // change listener, in case the osc target is invalidated
    
    void targetInvalidated (OSCTarget* _target) override;
    
private:
    
    String identifier;
    std::shared_ptr<OSCTarget> target;
    
};




#endif  // RELAY_H_INCLUDED
