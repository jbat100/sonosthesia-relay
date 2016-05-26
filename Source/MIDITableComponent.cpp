/*
  ==============================================================================

    MIDITableComponent.cpp
    Created: 12 May 2016 4:38:11pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

#include "RelayComponent.h"
#include "MIDITableComponent.h"

//==============================================================================
MIDITableComponent::MIDITableComponent(MIDIRelayManager& _relayManager, OSCTargetManager& _targetManager) :
relayManager(_relayManager),
targetManager(_targetManager)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    addAndMakeVisible(newButton);
    newButton.addListener(this);
    newButton.setButtonText("New");
    
    addAndMakeVisible(clearButton);
    clearButton.addListener(this);
    clearButton.setButtonText("Clear");
    
    // Create our table component and add it to this component..
    addAndMakeVisible (table);
    
    table.setModel (this);
    
    // give it a border
    table.setColour (ListBox::outlineColourId, Colours::grey);
    table.setOutlineThickness (1);
    
    TableHeaderComponent::ColumnPropertyFlags flags = (TableHeaderComponent::ColumnPropertyFlags)
    (TableHeaderComponent::ColumnPropertyFlags::visible |
     TableHeaderComponent::ColumnPropertyFlags::resizable);
    
    TableHeaderComponent::ColumnPropertyFlags buttonFlags = (TableHeaderComponent::ColumnPropertyFlags)
    (TableHeaderComponent::ColumnPropertyFlags::visible);
    
    table.getHeader().addColumn ("Channel", channelColumnId, 60, 50, 400, flags);
    table.getHeader().addColumn ("Target", targetColumnId, 200, 50, 400, flags);
    table.getHeader().addColumn ("Group", groupColumnId, 200, 50, 400, flags);
    table.getHeader().addColumn ("", buttonColumnId, 200, 50, 400, buttonFlags);
    
    table.setRowHeight(25);
    
    targetManager.addChangeListener(this);
}

MIDITableComponent::~MIDITableComponent()
{
}

void MIDITableComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
     draws some placeholder text to get you started.
     
     You should replace everything in this method with your own
     drawing code..
     */
    
    g.fillAll (Colours::white);   // clear the background
    
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    g.setColour (Colours::lightblue);
    g.setFont(14.0f);
    
    // draw some placeholder text
    // g.drawText ("MIDITableComponent", getLocalBounds(), Justification::centred, true);
}

void MIDITableComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains...
    
    int buttonHeight = 25;
    int margin = 4;
    
    int halfWidth = getBounds().getWidth() / 2;
    
    newButton.setBounds( getBounds().withX(0).withY(0).withHeight(buttonHeight).withWidth(halfWidth).reduced(margin) );
    clearButton.setBounds( getBounds().withX(halfWidth).withY(0).withHeight(buttonHeight).withWidth(halfWidth).reduced(margin) );
    
    table.setBounds( getBounds().withX(0).withY(buttonHeight).withTrimmedBottom(buttonHeight).reduced(margin) );
}


void MIDITableComponent::changeListenerCallback (ChangeBroadcaster *source)
{
    // if the targets change then we need to update the table so that the new targets are available
    if (source == dynamic_cast<ChangeBroadcaster*>(&targetManager))
    {
        std::cout << "MIDITableComponent updating table content on targetManager change\n";
        table.updateContent();
    }
}

// ======== Button::Listener =========

void MIDITableComponent::buttonClicked (Button* button)
{
    if (button == &newButton)
    {
        //std::cout << "Make new target!\n";
        relayManager.newItem();
        table.updateContent();
    }
    else if (button == &clearButton)
    {
        //std::cout << "Clear targets!\n";
        relayManager.clear();
        table.updateContent();
    }
}

// ======= TableListBoxModel =========

int MIDITableComponent::getNumRows()
{
    return relayManager.getItems().size();
}

void MIDITableComponent::paintRowBackground (Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected) g.fillAll (Colours::lightblue);
    else if (rowNumber % 2) g.fillAll (Colour (0xffeeeeee));
}

String MIDITableComponent::getCellText (const int columnId, const int rowNumber)
{
    std::shared_ptr<MIDIRelay> relay = relayManager.getItem(rowNumber);
    
    if (columnId == groupColumnId) return relay->getGroup();
    
    throw std::invalid_argument("unexpected columnId");
}

void MIDITableComponent::cellTextChanged (const int columnId, const int rowNumber, const String& newText)
{
    std::shared_ptr<MIDIRelay> relay = relayManager.getItem(rowNumber);
    
    if (columnId == groupColumnId) return relay->setGroup(String(newText));
    
    throw std::invalid_argument("unexpected columnId");
}

void MIDITableComponent::onCellDeleteButton (const int rowNumber)
{
    std::cout << "Delete row " << rowNumber << "\n";
    
    std::shared_ptr<MIDIRelay> relay = relayManager.getItems().at(rowNumber);
    
    relayManager.deleteItem(relay->getIdentifier());
    
    table.updateContent();
}

void MIDITableComponent::onCellDetailsButton (const int rowNumber)
{
    std::cout << "Details row " << rowNumber << "\n";
    
    //std::shared_ptr<MIDIRelay> relay = relayManager.getItems().at(rowNumber);
}

// This is overloaded from TableListBoxModel, and must update any custom components that we're using
Component* MIDITableComponent::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    
    if (columnId == buttonColumnId) // For the ratings column, we return the custom combobox component
    {
        ButtonCustomComponent* component = static_cast<ButtonCustomComponent*> (existingComponentToUpdate);
        
        // If an existing component is being passed-in for updating, we'll re-use it, but
        // if not, we'll have to create one.
        if (component == nullptr) component = new ButtonCustomComponent(*this);
        
        component->setRow(rowNumber);
        return component;
    }
    
    if (columnId == channelColumnId) // For the ratings column, we return the custom combobox component
    {
        ChannelColumnCustomComponent* component = static_cast<ChannelColumnCustomComponent*> (existingComponentToUpdate);
        
        // If an existing component is being passed-in for updating, we'll re-use it, but
        // if not, we'll have to create one.
        if (component == nullptr) component = new ChannelColumnCustomComponent();
        
        std::shared_ptr<MIDIRelay> relay = relayManager.getItem(rowNumber);
        
        component->setRelay(relay);
        return component;
    }
    
    if (columnId == targetColumnId) // For the ratings column, we return the custom combobox component
    {
        TargetColumnCustomComponent* component = static_cast<TargetColumnCustomComponent*> (existingComponentToUpdate);
        
        // If an existing component is being passed-in for updating, we'll re-use it, but
        // if not, we'll have to create one.
        if (component == nullptr) component = new TargetColumnCustomComponent(targetManager);
        
        std::shared_ptr<Relay> relay = std::static_pointer_cast<Relay>(relayManager.getItem(rowNumber));
        
        component->refresh();
        component->setRelay(relay);
        
        return component;
    }
    
    if (columnId == groupColumnId)
    {
        // The other columns are editable text columns, for which we use the custom Label component
        TextCellComponent* textLabel = static_cast<TextCellComponent*> (existingComponentToUpdate);
        
        // same as above...
        if (textLabel == nullptr)
            textLabel = new TextCellComponent (*this);
        
        textLabel->setRowAndColumn(rowNumber, columnId);
        return textLabel;
    }
    
    return nullptr;
    
}


// This is overloaded from TableListBoxModel, and must paint any cells that aren't using custom components.
void MIDITableComponent::paintCell (Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour (Colours::black);
}

int MIDITableComponent::getColumnAutoSizeWidth (int columnId)
{
    return 32;
}

