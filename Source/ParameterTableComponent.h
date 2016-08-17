/*
  ==============================================================================

    ParameterTableComponent.h
    Created: 12 May 2016 4:37:39pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef PARAMETERTABLECOMPONENT_H_INCLUDED
#define PARAMETERTABLECOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "PluginProcessor.h"
#include "CommonComponent.h"
#include "ParameterRelay.h"

//==============================================================================
/*
*/
class ParameterTableComponent : public Component, public Button::Listener, public TableListBoxModel, public ChangeListener, public TextCellManager
{
public:
    ParameterTableComponent(RelayAudioProcessor& processor);
    ~ParameterTableComponent();

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
    
    // ======= TextCellManager =========
    
    virtual String getCellText (const int columnNumber, const int rowNumber) override;
    virtual void cellTextChanged (const int columnId, const int rowNumber, const String& newText) override;
    
    // ======= TableListBox Helpers =========
    
    void onCellDeleteButton (const int rowNumber);
    void onCellDetailsButton (const int rowNumber);
    
private:
    
    TextButton newButton;
    TextButton clearButton;
    TableListBox table;
    Font font;
    
    const int parameterColumnId = 1;
    const int targetColumnId = 2;
    const int groupColumnId = 3;
    const int descriptorColumnId = 4;
    const int buttonColumnId = 5;
    
    RelayAudioProcessor& processor;
    
    class ParameterCellComponent : public Component, private ComboBoxListener
    {
    public:
        ParameterCellComponent (const OwnedArray<AudioProcessorParameter>& _parameters) :
        parameters(_parameters)
        {
            // just put a combo box inside this component
            addAndMakeVisible (comboBox);
            
            comboBox.addItem ( "None" , parameterIndexToId(ParameterRelay::noIndex) );
            
            for (auto i = parameters.begin(); i != parameters.end(); i++)
            {
                // can't have 0 as id so we offset by 1
                comboBox.addItem ( (*i)->getName(20) , parameterIndexToId((*i)->getParameterIndex()) );
            }
            
            // when the combo is changed, we'll get a callback.
            comboBox.addListener (this);
            comboBox.setWantsKeyboardFocus (false);
        }
        
        int parameterIndexToId(int parameterIndex)
        {
            return parameterIndex + 2; // we want to avoid 0
        }
        
        int idToParameterIndex(int _id)
        {
            return _id - 2;
        }
        
        void resized() override
        {
            comboBox.setBoundsInset (BorderSize<int> (2));
        }
        
        void comboBoxChanged (ComboBox*) override
        {
            relay->setIndex ( idToParameterIndex(comboBox.getSelectedId()) );
        }
        
        void setRelay(std::shared_ptr<ParameterRelay> _relay)
        {
            relay = _relay;
            if (relay) comboBox.setSelectedId( parameterIndexToId(relay->getIndex()) );
            else comboBox.setSelectedId( parameterIndexToId(ParameterRelay::noIndex) );
        }
        
    private:
        ComboBox comboBox;
        std::shared_ptr<ParameterRelay> relay;
        const OwnedArray<AudioProcessorParameter>& parameters;
    };
    
    //==============================================================================
    // This is a custom Label component, which we use for the table's editable text columns.
    class ButtonCustomComponent  : public Component, public ButtonListener
    {
    public:
        ButtonCustomComponent (ParameterTableComponent& td)  : owner (td)
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
        ParameterTableComponent& owner;
        TextButton deleteButton, detailsButton;
        int row;
    };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterTableComponent)
};


#endif  // PARAMETERTABLECOMPONENT_H_INCLUDED
