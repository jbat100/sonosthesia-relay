/*
  ==============================================================================

    RelayComponent.h
    Created: 16 May 2016 4:07:30pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef RELAYCOMPONENT_H_INCLUDED
#define RELAYCOMPONENT_H_INCLUDED

#include "Utils.h"
#include "Relay.h"
#include "OSCTargetManager.h"

#include <map>

//==============================================================================
// This is a custom component containing used for selecting a midi channel
class TargetColumnCustomComponent : public Component, private ComboBoxListener
{
public:
    TargetColumnCustomComponent (OSCTargetManager& _manager) : manager(_manager)
    {
        // just put a combo box inside this component
        addAndMakeVisible (comboBox);
        
        //comboBox.addItem ("All", -1);
        
        comboBox.addListener (this);
        comboBox.setWantsKeyboardFocus (false);
    }
    
    void resized() override
    {
        comboBox.setBoundsInset (BorderSize<int> (2));
    }
    
    void setRelay (std::shared_ptr<Relay> _relay)
    {
        relay = _relay;
        int numericIdentifier = generator.getNumericIdentifier(relay->getTarget()->getIdentifier());
        comboBox.setSelectedId (numericIdentifier, dontSendNotification);
    }
    
    void comboBoxChanged (ComboBox*) override
    {
        String identifier = generator.getStringIdentifier(comboBox.getSelectedId());
        std::shared_ptr<OSCTarget> target = manager.getTarget(identifier);
        relay->setTarget (target);
    }
    
private:
    ComboBox comboBox;
    std::shared_ptr<Relay> relay;
    OSCTargetManager& manager;
    NumericIdentifierGenerator generator;
};


#endif  // RELAYCOMPONENT_H_INCLUDED
