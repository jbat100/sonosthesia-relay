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

#include "Utils.h"
#include "OSCTargetManager.h"

//==============================================================================
/*
*/
class TargetComponent    : public Component, public Button::Listener, public TableListBoxModel, public TextCellManager
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
    int getColumnAutoSizeWidth (int columnId) override;
    
    // ======= TextCellManager =========
    
    virtual String getCellText (const int columnNumber, const int rowNumber) override;
    virtual void cellTextChanged (const int columnId, const int rowNumber, const String& newText) override;
    
    // ======= TableListBox Helpers =========
    
    void onCellDeleteButton (const int rowNumber);
    void onCellConnectButton (const int rowNumber);

private:
    
    TextButton newButton;
    TextButton clearButton;
    TableListBox table;
    Font font;
    
    const int hostnameColumnId = 1;
    const int portColumnId = 2;
    const int statusColumnId = 3;
    const int buttonColumnId = 4;
    
    OSCTargetManager& oscTargetManager;
    
    //==============================================================================
    // This is a custom Label component, which we use for the table's editable text columns.
    class ButtonCustomComponent  : public Component, public ButtonListener
    {
    public:
        ButtonCustomComponent (TargetComponent& td)  : owner (td)
        {
            addAndMakeVisible(deleteButton);
            deleteButton.setButtonText("Delete");
            deleteButton.addListener(this);
            
            addAndMakeVisible(connectButton);
            connectButton.setButtonText("Reconnect");
            connectButton.addListener(this);
            
        }
        
        void resized() override
        {
            Rectangle<int> b = getBounds();
            int halfWidth = b.getWidth() / 2;
            b.setWidth( halfWidth );
            
            deleteButton.setBounds( b.withX(0).reduced(4) );
            connectButton.setBounds( b.withX(halfWidth).reduced(4) );
        }
        
        void buttonClicked (Button* button) override
        {
            if (button == &deleteButton)
            {
                owner.onCellDeleteButton(row);
            }
            else if (button == &connectButton)
            {
                owner.onCellConnectButton(row);
            }
        }
        
        void setRowAndColumn (const int newRow, const int newColumn)
        {
            row = newRow;
            columnId = newColumn;
        }
        
    private:
        TargetComponent& owner;
        TextButton deleteButton, connectButton;
        int row, columnId;
    };
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TargetComponent)
};




#endif  // TARGETCOMPONENT_H_INCLUDED
