/*
  ==============================================================================

    MIDIListComponent.cpp
    Created: 26 May 2016 2:59:59pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MIDIListComponent.h"
#include "Theme.h"


const int MIDIRelayComponent::desiredHeight = 60;
const int MIDIRelayComponent::hmargin = 10;
const int MIDIRelayComponent::vmargin = 4;


// MIDIChannelSelectionComponent

const String MIDIChannelSelectionComponent::allChannelsText = "All";
const String MIDIChannelSelectionComponent::noChannelText = "None";

MIDIChannelSelectionComponent::MIDIChannelSelectionComponent ()
{
    // just put a combo box inside this component
    addAndMakeVisible (comboBox);
    
    comboBox.addItem (noChannelText, MIDIRelay::noChannel);
    comboBox.addItem (allChannelsText, MIDIRelay::allChannels);
    
    for (int i = 1; i <= 16; i++)
    {
        comboBox.addItem ( String(i) , i );
    }
    
    // when the combo is changed, we'll get a callback.
    comboBox.addListener (this);
    comboBox.setWantsKeyboardFocus (false);
}

void MIDIChannelSelectionComponent::resized()
{
    //comboBox.setBoundsInset (BorderSize<int> (2));
    
    comboBox.setBounds( getLocalBounds() );
}

void MIDIChannelSelectionComponent::refresh()
{
    if (relay)
    {
        int channel = relay->getChannel();
        //std::cout << "---> " << channel << "\n";
        comboBox.setSelectedId ( channel, dontSendNotification);
    }
    else
    {
        comboBox.setSelectedId ( MIDIRelay::noChannel, dontSendNotification);
    }
}

void MIDIChannelSelectionComponent::setRelay (std::shared_ptr<MIDIRelay> _relay)
{
    relay = _relay;
    refresh();
}

void MIDIChannelSelectionComponent::comboBoxChanged (ComboBox*)
{
    if (relay)
    {
        relay->setChannel ( comboBox.getSelectedId() );
    }
}


// MIDIRelayComponent


MIDIRelayComponent::MIDIRelayComponent(OSCTargetManager& _targetManager, MIDIRelayManager& _relayManager) :
    RelayComponent(_targetManager),
    relayManager(_relayManager)
{
    
    setOpaque(false);
    
    addAndMakeVisible(channelSelectionComponent);
    
    addAndMakeVisible(channelLabel);
    channelLabel.setText("Channel", dontSendNotification);
    Appearence::theme()->label(channelLabel);
}

void MIDIRelayComponent::paint (Graphics& g)
{
    g.fillAll (Colours::transparentBlack);   // clear the background
    
    Rectangle<float> b = getLocalBounds().toFloat();
    Rectangle<float> cellBounds(hmargin, vmargin, b.getWidth() - (hmargin*2), b.getHeight() - (vmargin*2));
    
    g.setColour (Colours::grey);
    g.drawRoundedRectangle(cellBounds, 5, 1);
    g.setColour(Colours::black.withAlpha(0.5f));
    g.fillRoundedRectangle(cellBounds.reduced(1), 5);
}

void MIDIRelayComponent::resized()
{
    int hspacing = 10;
    int vspacing = 6;
    
    // target   <________________________> | Del |
    // channel  ____  group <____________> |     |
    
    int targetLabelWidth = 60;
    int channelLabelWidth = 60;
    int channelSelectorWidth = 60;
    int groupLabelWidth = 60;
    int buttonWidth = 60;
    int rowHeight = 20;
    
    Rectangle<int> bounds = getBounds();
    
    // double margin, for the outer and inner component cell
    //Rectangle<int> rootBounds = getBounds().reduced(hmargin*4, vmargin*4).translated(hmargin*2, vmargin*2);
    
    int hackyOffset = 10;
    Rectangle<int> rootBounds = getBounds().reduced(hmargin*2, vmargin*2).translated(hmargin - hackyOffset, vmargin);
    int fullWidth = rootBounds.getWidth();
    
    // ROW1
    
    int horizontalOffset = rootBounds.getX();
    int verticalOffset = rootBounds.getY();
    
    Rectangle<int> targetLabelBounds(horizontalOffset, verticalOffset, targetLabelWidth, rowHeight);
    horizontalOffset = targetLabelBounds.getRight() + hspacing;
    targetLabel.setBounds(targetLabelBounds);
    
    int targetSelectorWidth = fullWidth - targetLabelWidth - buttonWidth - (hspacing*2);
    Rectangle<int> targetSelectorBounds(horizontalOffset, verticalOffset, targetSelectorWidth, rowHeight);
    horizontalOffset = targetSelectorBounds.getRight() + hspacing;
    targetSelectionComponent.setBounds(targetSelectorBounds);
    
    // ROW2
    
    horizontalOffset = rootBounds.getX();
    verticalOffset = rootBounds.getY() + vspacing + rowHeight;
    
    Rectangle<int> channelLabelBounds(horizontalOffset, verticalOffset, channelLabelWidth, rowHeight);
    horizontalOffset = channelLabelBounds.getRight() + hspacing;
    channelLabel.setBounds(channelLabelBounds);
    
    Rectangle<int> channelSelectorBounds(horizontalOffset, verticalOffset, channelSelectorWidth, rowHeight);
    horizontalOffset = channelSelectorBounds.getRight() + hspacing;
    channelSelectionComponent.setBounds(channelSelectorBounds);
    
    Rectangle<int> groupLabelBounds(horizontalOffset, verticalOffset, groupLabelWidth, rowHeight);
    horizontalOffset = groupLabelBounds.getRight() + hspacing;
    groupLabel.setBounds(groupLabelBounds);
    
    int groupFieldWidth = fullWidth - channelLabelWidth - channelSelectorWidth - groupLabelWidth - buttonWidth - (hspacing*4);
    Rectangle<int> groupFieldBounds(horizontalOffset, verticalOffset, groupFieldWidth, rowHeight);
    horizontalOffset = groupFieldBounds.getRight() + hspacing;
    groupField.setBounds(groupFieldBounds);
    
    // BUTTON
    
    horizontalOffset = rootBounds.getX() + fullWidth - buttonWidth;
    verticalOffset = rootBounds.getY();
    
    //int buttonHeight = (rowHeight * 2) + vspacing; // spans two rows
    Rectangle<int> buttonBounds(horizontalOffset, verticalOffset, buttonWidth, rowHeight);
    deleteButton.setBounds(buttonBounds);

}

void MIDIRelayComponent::setRelay(std::shared_ptr<Relay> _relay)
{
    std::shared_ptr<MIDIRelay> midiRelay = std::dynamic_pointer_cast<MIDIRelay>(_relay);
    
    channelSelectionComponent.setRelay(midiRelay);
    
    RelayComponent::setRelay( _relay );
}


void MIDIRelayComponent::refresh()
{
    RelayComponent::refresh();
    
    channelSelectionComponent.refresh();
}

void MIDIRelayComponent::buttonClicked (Button* button)
{
    if (button == &deleteButton)
    {
        if (relay) relayManager.deleteItem(relay->getIdentifier());
    }
}


MIDIListComponent::MIDIListComponent(MIDIRelayManager& _relayManager, OSCTargetManager& _targetManager) :
    listController("Relay MIDI messages to OSC targets"),
    targetManager(_targetManager),
    relayManager(_relayManager)
{
    relayManager.addChangeListener(this);
    
    setOpaque(false);
    
    /*
    addAndMakeVisible(newButton);
    newButton.addListener(this);
    newButton.setButtonText("New");
    
    addAndMakeVisible(clearButton);
    clearButton.addListener(this);
    clearButton.setButtonText("Clear");
     */
    
    addAndMakeVisible(listController);
    listController.add(this);
    
    // Create our table component and add it to this component..
    addAndMakeVisible (listBox);
    
    listBox.setOutlineThickness(0);
    listBox.setRowHeight(MIDIRelayComponent::desiredHeight + 10);
    
    listBox.setOpaque(false);
    listBox.setColour(ListBox::ColourIds::backgroundColourId, Colours::transparentBlack);
    
    listBox.setModel (this);
}


void MIDIListComponent::resized()
{
    int controllerHeight = 45;
    int hmargin = 4;
    int vmargin = 4;
    int vspacing = 4;
    
    Rectangle<int> rootBounds = getBounds();
    //Rectangle<int> rootBounds = getBounds().reduced(hmargin*2, vmargin*2).translated(hmargin, vmargin);
    int verticalOffset = vmargin;
    int width = rootBounds.getWidth();
    
    int listHeight = rootBounds.getHeight() - controllerHeight;
    
    listBox.setBounds( Rectangle<int>(hmargin, vmargin, width, listHeight) );
    verticalOffset = listBox.getBottom() + vspacing;
    
    listController.setBounds( Rectangle<int>(0, verticalOffset, width, controllerHeight) );
}

void MIDIListComponent::changeListenerCallback (ChangeBroadcaster *source)
{
    // if the targets change then we need to update the table so that the new targets are available
    if (source == dynamic_cast<ChangeBroadcaster*>(&relayManager))
    {
        std::cout << "MIDIListComponent updating table content on targetManager change\n";
        listBox.updateContent();
    }
}

void MIDIListComponent::newItemRequest(Component* sender)
{
    relayManager.newItem();
    listBox.updateContent();
}

void MIDIListComponent::clearItemsRequest(Component* sender)
{
    relayManager.clear();
    listBox.updateContent();
}

void MIDIListComponent::buttonClicked (Button* button)
{
    if (button == &newButton)
    {
        //std::cout << "Make new target!\n";
        relayManager.newItem();
        listBox.updateContent();
    }
    else if (button == &clearButton)
    {
        //std::cout << "Clear targets!\n";
        relayManager.clear();
        listBox.updateContent();
    }
}

int MIDIListComponent::getNumRows()
{
    return relayManager.getItems().size();
}

void MIDIListComponent::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
    
}

Component* MIDIListComponent::refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate)
{
    MIDIRelayComponent* relayComponent = static_cast<MIDIRelayComponent*> (existingComponentToUpdate);
    
    std::shared_ptr<MIDIRelay> relay = nullptr;
    
    if (rowNumber < relayManager.count())
    {
        relay = relayManager.getItem(rowNumber);
    }
    
    // If an existing component is being passed-in for updating, we'll re-use it, if not, we'll have to create one.
    if (relayComponent == nullptr)
    {
        relayComponent = new MIDIRelayComponent(targetManager, relayManager);
    }
    
    relayComponent->setRelay(relay);
    return relayComponent;
}

