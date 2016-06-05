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
    
    MIDIChannelSelectionComponent ();
    virtual ~MIDIChannelSelectionComponent() {}
    
    void refresh();
    
    void setRelay (std::shared_ptr<MIDIRelay> _relay);
    
    virtual void resized() override;
    
    virtual void comboBoxChanged (ComboBox*) override;
    
private:
    
    static const String noChannelText;
    static const String allChannelsText;
    
    ComboBox comboBox;
    std::shared_ptr<MIDIRelay> relay;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MIDIChannelSelectionComponent)
};

//==============================================================================
/*  A component associated with a target
 */

class MIDIRelayComponent : public RelayComponent {
    
public:
    
    MIDIRelayComponent(OSCTargetManager& _targetManager, MIDIRelayManager& _relayManager);
    virtual ~MIDIRelayComponent() {}
    
    virtual void refresh() override;
    
    virtual void setRelay (std::shared_ptr<Relay> _relay) override;
    
    // ======== Component ==========
    
    virtual void paint (Graphics&) override;
    
    virtual void resized() override;
    
    // ======== ButtonListener =========
    
    virtual void buttonClicked (Button* button) override;
    
    static const int desiredHeight;
    static const int hmargin;
    static const int vmargin;
    
private:
    
    MIDIRelayManager& relayManager;
    
    Label channelLabel;
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
    ~MIDIListComponent() {}
    
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
