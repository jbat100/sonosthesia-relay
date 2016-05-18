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
class MIDIComponent : public Component, public Button::Listener, public TableListBoxModel, public ChangeListener
{
public:
    MIDIComponent(MIDIRelayManager& _relayManager, OSCTargetManager& _targetManager);
    ~MIDIComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    // ======= ChangeListener ===========
    
    void changeListenerCallback (ChangeBroadcaster *source) override;
    
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
    OSCTargetManager& targetManager;
    
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
    };
    
    
    //==============================================================================
    // This is a custom Label component, which we use for the table's editable text columns.
    class ButtonCustomComponent  : public Component, public ButtonListener
    {
    public:
        ButtonCustomComponent (MIDIComponent& td)  : owner (td)
        {
            addAndMakeVisible(deleteButton);
            deleteButton.setButtonText("Delete");
            deleteButton.addListener(this);
            
            addAndMakeVisible(detailsButton);
            detailsButton.setButtonText("Details");
            detailsButton.addListener(this);
            
        }
        
        void resized() override
        {
            Rectangle<int> b = getBounds();
            int halfWidth = b.getWidth() / 2;
            b.setWidth( halfWidth );
            
            deleteButton.setBounds( b.withX(0).reduced(4) );
            detailsButton.setBounds( b.withX(halfWidth).reduced(4) );
        }
        
        void buttonClicked (Button* button) override
        {
            if (button == &deleteButton)
            {
                owner.onCellDeleteButton(row);
            }
            else if (button == &detailsButton)
            {
                owner.onCellDetailsButton(row);
            }
        }
        
        void setRow (const int newRow)
        {
            row = newRow;
        }
        
    private:
        MIDIComponent& owner;
        TextButton deleteButton, detailsButton;
        int row;
    };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MIDIComponent)
};


#endif  // MIDICOMPONENT_H_INCLUDED
