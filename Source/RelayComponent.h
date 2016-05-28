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
        
        comboBox.setTextWhenNothingSelected("None");
        comboBox.addListener (this);
        comboBox.setWantsKeyboardFocus (false);
    }
    
    void resized() override
    {
        comboBox.setBoundsInset (BorderSize<int> (2));
    }
    
    void refresh()
    {
        updateComboBox();
    }
    
    void setRelay (std::shared_ptr<Relay> _relay)
    {
        relay = _relay;
        if (relay)
        {
            std::shared_ptr<OSCTarget> target = relay->getTarget();
            if (target)
            {
                int numericIdentifier = generator.getNumericIdentifier(target->getIdentifier());
                comboBox.setSelectedId (numericIdentifier, dontSendNotification);
                return;
            }
        }
        comboBox.setSelectedId (-1, dontSendNotification);
        
    }
    
    void comboBoxChanged (ComboBox*) override
    {
        try
        {
            int numericIdentifier = comboBox.getSelectedId();
            
            if (numericIdentifier == -1)
            {
                relay->setTarget (nullptr);
            }
            else if (numericIdentifier > 0)
            {
                String identifier = generator.getStringIdentifier(numericIdentifier);
                std::shared_ptr<OSCTarget> target = manager.getItem(identifier);
                relay->setTarget (target);
            }
        }
        catch (std::invalid_argument& err)
        {
            std::cerr << "TargetColumnCustomComponent comboBoxChanged exception: " << &err << "\n";
        }
        
    }
    
private:
    
    void updateComboBox() {
        
        const std::vector< std::shared_ptr<OSCTarget> > targets = manager.getItems();
        
        comboBox.clear();
        
        for (auto i = targets.begin(); i != targets.end(); i++)
        {
            int numericIdentifier = generator.getNumericIdentifier( (*i)->getIdentifier() );
            String description = (*i)->getHostName() + ":" + String((*i)->getPortNumber());
            comboBox.addItem(description, numericIdentifier);
        }
        
        setRelay(relay);
        
    }
    
    ComboBox comboBox;
    std::shared_ptr<Relay> relay;
    OSCTargetManager& manager;
    NumericIdentifierGenerator generator;
};



#endif  // RELAYCOMPONENT_H_INCLUDED
