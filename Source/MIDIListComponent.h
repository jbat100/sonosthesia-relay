/*
  ==============================================================================

    MIDIListComponent.h
    Created: 26 May 2016 2:59:59pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef MIDILISTCOMPONENT_H_INCLUDED
#define MIDILISTCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "OSCTargetManager.h"
#include "MIDIRelay.h"
#include "RelayComponent.h"


//==============================================================================
// This is a custom component containing used for selecting a midi channel
class MIDIChannelSelectionComponent : public Component, private ComboBoxListener
{
public:
    MIDIChannelSelectionComponent ()
    {
        // just put a combo box inside this component
        addAndMakeVisible (comboBox);
        
        comboBox.addItem ("All", -1);
        
        for (int i = 0; i < 16; i++)
        {
            // can't have 0 as id so we offset by 1
            comboBox.addItem (String(i) , idForChannel(i));
        }
        
        // when the combo is changed, we'll get a callback.
        comboBox.addListener (this);
        comboBox.setWantsKeyboardFocus (false);
    }
    
    int idForChannel(int channel)
    {
        if (channel == -1) return channel;
        else if (channel >= 0) return channel + 1;
        throw std::invalid_argument("unexpected channel");
    }
    
    int channelForId(int _id)
    {
        if (_id == -1) return _id;
        else if (_id > 0) return _id - 1;
        throw std::invalid_argument("unexpected _id");
    }
    
    void resized() override
    {
        comboBox.setBoundsInset (BorderSize<int> (2));
    }
    
    void setRelay (std::shared_ptr<MIDIRelay> _relay)
    {
        relay = _relay;
        comboBox.setSelectedId (idForChannel(relay->getChannel()), dontSendNotification);
    }
    
    void comboBoxChanged (ComboBox*) override
    {
        relay->setChannel ( channelForId(comboBox.getSelectedId()) );
    }
    
private:
    
    ComboBox comboBox;
    std::shared_ptr<MIDIRelay> relay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MIDIChannelSelectionComponent)
};

//==============================================================================
/*  A component associated with a target
 */

class MIDIRelayComponent : public RelayComponent {
    
public:
    
    MIDIRelayComponent(OSCTargetManager& _targetManager);
    
    void setMIDIRelay(std::shared_ptr<MIDIRelay> _relay);
    
    std::shared_ptr<MIDIRelay> getMIDIRelay();
    
    virtual void refresh() override;
    
    // ======== LabelListener ==========
    
    virtual void labelTextChanged(Label *label) override;
    
    // ======== ButtonListener =========
    
    virtual void buttonClicked (Button* button) override;
    
private:
    
    MIDIChannelSelectionComponent channelSelectionComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MIDIRelayComponent)
    
};

//==============================================================================
/*  A component presenting a list of targets
 */

class MIDIListComponent : public Component, public ButtonListener, public ListBoxModel, public ChangeListener
{
public:
    MIDIListComponent(MIDIRelayManager& _relayManager, OSCTargetManager& _targetManager);
    ~MIDIListComponent();
    
    void paint (Graphics&) override;
    void resized() override;
    
    // ======= ChangeListener ===========
    
    void changeListenerCallback (ChangeBroadcaster *source) override;
    
    // ======== ButtonListener =========
    
    void buttonClicked (Button* button) override;
    
    // ======== ListBoxModel ===========
    
    int getNumRows() override;
    void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) override;
    
private:
    
    TextButton newButton;
    TextButton clearButton;
    ListBox listBox;
    Font font;
    
    OSCTargetManager& targetManager;
    MIDIRelayManager& relayManager;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MIDIListComponent)
};


#endif  // MIDILISTCOMPONENT_H_INCLUDED
