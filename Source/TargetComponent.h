/*
  ==============================================================================

    TargetComponent.h
    Created: 12 May 2016 4:37:10pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef TARGETCOMPONENT_H_INCLUDED
#define TARGETCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "OSCTargetManager.h"

//==============================================================================
/*
*/
class TargetComponent    : public Component, public Button::Listener, public TableListBoxModel
{
public:
    TargetComponent(OSCTargetManager& _oscTargetManager);
    ~TargetComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    // ======== Button::Listener =========
    
    void buttonClicked (Button* button) override;
    
    // ======= TableListBoxModel =========
    
    int getNumRows() override;
    void paintRowBackground (Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell (Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
    
    // ======= TableListBox Helpers =========
    
    String getText (const int columnNumber, const int rowNumber) const;
    void setText (const int columnId, const int rowNumber, const String& newText);

private:
    
    TextButton newButton;
    TableListBox table;
    Font font;
    
    const int hostnameColumnId = 1;
    const int portColumnId = 2;
    const int connectedColumnId = 3;
    const int connectColumnId = 4;
    
    OSCTargetManager& oscTargetManager;
    
    //==============================================================================
    // This is a custom Label component, which we use for the table's editable text columns.
    class EditableTextCustomComponent  : public Label
    {
    public:
        EditableTextCustomComponent (TargetComponent& td)  : owner (td)
        {
            // double click to edit the label text; single click handled below
            setEditable (false, true, false);
            setColour (textColourId, Colours::black);
        }
        
        void textWasEdited() override
        {
            owner.setText (columnId, row, getText());
        }
        
        void setRowAndColumn (const int newRow, const int newColumn)
        {
            row = newRow;
            columnId = newColumn;
            setText (owner.getText(columnId, row), dontSendNotification);
        }
        
    private:
        TargetComponent& owner;
        int row, columnId;
    };
    
    //==============================================================================
    // This is a custom Label component, which we use for the table's editable text columns.
    class ButtonCustomComponent  : public Component, public ButtonListener
    {
    public:
        ButtonCustomComponent (TargetComponent& td)  : owner (td)
        {
            addAndMakeVisible(button);
        }
        
        void resized() override
        {
            button.setBounds(getBounds());
        }
        
        void buttonClicked (Button* button) override
        {
            
        }
        
        void setRowAndColumn (const int newRow, const int newColumn)
        {
            row = newRow;
            columnId = newColumn;
            //setText (owner.get(columnId, row), dontSendNotification);
        }
        
    private:
        TargetComponent& owner;
        TextButton button;
        int row, columnId;
    };
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TargetComponent)
};


#endif  // TARGETCOMPONENT_H_INCLUDED
