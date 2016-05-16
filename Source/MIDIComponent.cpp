/*
  ==============================================================================

    MIDIComponent.cpp
    Created: 12 May 2016 4:38:11pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MIDIComponent.h"

//==============================================================================
MIDIComponent::MIDIComponent(MIDIRelayManager& _relayManager) : relayManager(_relayManager)
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
    
    table.getHeader().addColumn ("Channel", channelColumnId, 250, 50, 400, flags);
    table.getHeader().addColumn ("Target", targetColumnId, 60, 50, 400, flags);
    table.getHeader().addColumn ("", buttonColumnId, 200, 50, 400, buttonFlags);
    
    table.setRowHeight(25);
    
}

MIDIComponent::~MIDIComponent()
{
}

void MIDIComponent::paint (Graphics& g)
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
    // g.drawText ("MIDIComponent", getLocalBounds(), Justification::centred, true);
}

void MIDIComponent::resized()
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


// ======== Button::Listener =========

void MIDIComponent::buttonClicked (Button* button)
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

int MIDIComponent::getNumRows()
{
    return relayManager.getItems().size();
}

void MIDIComponent::paintRowBackground (Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected) g.fillAll (Colours::lightblue);
    else if (rowNumber % 2) g.fillAll (Colour (0xffeeeeee));
}


void MIDIComponent::onCellDeleteButton (const int rowNumber)
{
    std::cout << "Delete row " << rowNumber << "\n";
    
    std::shared_ptr<MIDIRelay> relay = relayManager.getItems().at(rowNumber);
    
    relayManager.deleteItem(relay->getIdentifier());
    
    table.updateContent();
}

void MIDIComponent::onCellDetailsButton (const int rowNumber)
{
    std::cout << "Details row " << rowNumber << "\n";
    
    //std::shared_ptr<MIDIRelay> relay = relayManager.getItems().at(rowNumber);
}

// This is overloaded from TableListBoxModel, and must update any custom components that we're using
Component* MIDIComponent::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    
    /*
    
    if (columnId == buttonColumnId) // For the ratings column, we return the custom combobox component
    {
        ButtonCustomComponent* connectComponent = static_cast<ButtonCustomComponent*> (existingComponentToUpdate);
        
        // If an existing component is being passed-in for updating, we'll re-use it, but
        // if not, we'll have to create one.
        if (connectComponent == nullptr) connectComponent = new ButtonCustomComponent(*this);
        
        connectComponent->setRowAndColumn(rowNumber, columnId);
        return connectComponent;
    }
    
    if (columnId == channelColumnId) // For the ratings column, we return the custom combobox component
    {
        ButtonCustomComponent* connectComponent = static_cast<ButtonCustomComponent*> (existingComponentToUpdate);
        
        // If an existing component is being passed-in for updating, we'll re-use it, but
        // if not, we'll have to create one.
        if (connectComponent == nullptr) connectComponent = new ButtonCustomComponent(*this);
        
        connectComponent->setRowAndColumn(rowNumber, columnId);
        return connectComponent;
    }
    
    if (columnId == targetColumnId) // For the ratings column, we return the custom combobox component
    {
        ButtonCustomComponent* connectComponent = static_cast<ButtonCustomComponent*> (existingComponentToUpdate);
        
        // If an existing component is being passed-in for updating, we'll re-use it, but
        // if not, we'll have to create one.
        if (connectComponent == nullptr) connectComponent = new ButtonCustomComponent(*this);
        
        connectComponent->setRowAndColumn(rowNumber, columnId);
        return connectComponent;
    }
     
     */
    
}


// This is overloaded from TableListBoxModel, and must paint any cells that aren't using custom components.
void MIDIComponent::paintCell (Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour (Colours::black);
}

int MIDIComponent::getColumnAutoSizeWidth (int columnId)
{
    return 32;
}

