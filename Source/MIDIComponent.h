/*
  ==============================================================================

    MIDIComponent.h
    Created: 12 May 2016 4:38:11pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef MIDICOMPONENT_H_INCLUDED
#define MIDICOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "MIDIRelay.h"

//==============================================================================
/*
*/
class MIDIComponent : public Component, public Button::Listener, public TableListBoxModel
{
public:
    MIDIComponent(MIDIRelayManager& _relayManager);
    ~MIDIComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    // ======== Button::Listener =========
    
    void buttonClicked (Button* button) override;
    
    // ======= TableListBoxModel =========
    
    int getNumRows() override;
    void paintRowBackground (Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
    void paintCell (Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    int getColumnAutoSizeWidth (int columnId) override;
    
    // ======= TableListBox Helpers =========
    
    void onCellDeleteButton (const int rowNumber);
    void onCellDetailsButton (const int rowNumber);
    
private:
    
    TextButton newButton;
    TextButton clearButton;
    TableListBox table;
    Font font;
    
    const int channelColumnId = 1;
    const int targetColumnId = 2;
    const int buttonColumnId = 4;
    
    MIDIRelayManager& relayManager;
    
    //==============================================================================
    // This is a custom component containing used for selecting a midi channel
    class ChannelColumnCustomComponent : public Component, private ComboBoxListener
    {
    public:
        ChannelColumnCustomComponent ()
        {
            // just put a combo box inside this component
            addAndMakeVisible (comboBox);
            
            comboBox.addItem ("All", -1);
            
            for (int i = 0; i < 16; i++)
            {
                comboBox.addItem (String(i) , i);
            }
            
            // when the combo is changed, we'll get a callback.
            comboBox.addListener (this);
            comboBox.setWantsKeyboardFocus (false);
        }
        
        void resized() override
        {
            comboBox.setBoundsInset (BorderSize<int> (2));
        }
        
        void setRelay (std::shared_ptr<MIDIRelay> _relay)
        {
            relay = _relay;
            comboBox.setSelectedId (relay->getChannel(), dontSendNotification);
        }
        
        void comboBoxChanged (ComboBox*) override
        {
            relay->setChannel (comboBox.getSelectedId());
        }
        
    private:
        ComboBox comboBox;
        std::shared_ptr<MIDIRelay> relay;
    };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MIDIComponent)
};


#endif  // MIDICOMPONENT_H_INCLUDED
