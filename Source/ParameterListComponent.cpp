/*
  ==============================================================================

    ParameterListComponent.cpp
    Created: 26 May 2016 3:00:19pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ParameterListComponent.h"
#include "Theme.h"

ParameterSelectionComponent::ParameterSelectionComponent (const OwnedArray<AudioProcessorParameter>& _parameters) :
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

int ParameterSelectionComponent::parameterIndexToId(int parameterIndex)
{
    return parameterIndex + 2; // we want to avoid 0
}

int ParameterSelectionComponent::idToParameterIndex(int _id)
{
    return _id - 2;
}

void ParameterSelectionComponent::resized()
{
    comboBox.setBounds ( getLocalBounds() );
}

void ParameterSelectionComponent::comboBoxChanged (ComboBox*)
{
    if (relay)
    {
        relay->setIndex ( idToParameterIndex(comboBox.getSelectedId()) );
    }
}

void ParameterSelectionComponent::refresh()
{
    if (relay)
    {
        comboBox.setSelectedId( parameterIndexToId(relay->getIndex()) );
    }
    else
    {
        comboBox.setSelectedId( parameterIndexToId(ParameterRelay::noIndex) );
    }
}

void ParameterSelectionComponent::setRelay(std::shared_ptr<ParameterRelay> _relay)
{
    relay = _relay;
    refresh();
}



const int ParameterRelayComponent::desiredHeight = 60;
const int ParameterRelayComponent::hmargin = 10;
const int ParameterRelayComponent::vmargin = 4;

// ParameterRelayComponent


ParameterRelayComponent::ParameterRelayComponent(RelayAudioProcessor& _processor) :
    RelayComponent(_processor.getOSCTargetManager()),
    processor(_processor),
    parameterSelectionComponent(_processor.getParameters())
{
    setOpaque(false);
    
    addAndMakeVisible(parameterLabel);
    parameterLabel.setText("Parameter", dontSendNotification);
    Appearence::theme()->label(parameterLabel);
    
    addAndMakeVisible(parameterSelectionComponent);
    
    addAndMakeVisible(descriptorLabel);
    descriptorLabel.setText("Descriptor", dontSendNotification);
    Appearence::theme()->label(descriptorLabel);
    
    addAndMakeVisible(descriptorField);
    descriptorField.setEditable(false, true, false);
    descriptorField.addListener(this);
    Appearence::theme()->field(descriptorField);
}

void ParameterRelayComponent::paint (Graphics& g)
{
    g.fillAll (Colours::transparentBlack);   // clear the background
    
    Rectangle<float> b = getLocalBounds().toFloat();
    Rectangle<float> cellBounds(hmargin, vmargin, b.getWidth() - (hmargin*2), b.getHeight() - (vmargin*2));
    
    g.setColour (Colours::grey);
    g.drawRoundedRectangle(cellBounds, 5, 1);
    g.setColour(Colours::black.withAlpha(0.5f));
    g.fillRoundedRectangle(cellBounds.reduced(1), 5);
}

void ParameterRelayComponent::resized()
{
    int hspacing = 10;
    int vspacing = 6;
    
    // target   <__________________> parameter ______ | Del |
    // group <____________> descriptor <____________> |     |
    
    int targetLabelWidth = 60;
    int parameterLabelWidth = 80;
    int groupLabelWidth = 60;
    int descriptorLabelWidth = 80;
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
    
    int flexWidth = (fullWidth - targetLabelWidth - parameterLabelWidth - buttonWidth - (hspacing*4)) / 2;
    
    Rectangle<int> targetLabelBounds(horizontalOffset, verticalOffset, targetLabelWidth, rowHeight);
    horizontalOffset = targetLabelBounds.getRight() + hspacing;
    targetLabel.setBounds(targetLabelBounds);
    
    Rectangle<int> targetSelectorBounds(horizontalOffset, verticalOffset, flexWidth, rowHeight);
    horizontalOffset = targetSelectorBounds.getRight() + hspacing;
    targetSelectionComponent.setBounds(targetSelectorBounds);
    
    Rectangle<int> parameterLabelBounds(horizontalOffset, verticalOffset, parameterLabelWidth, rowHeight);
    horizontalOffset = parameterLabelBounds.getRight() + hspacing;
    parameterLabel.setBounds(parameterLabelBounds);
    
    Rectangle<int> parameterSelectionBounds(horizontalOffset, verticalOffset, flexWidth, rowHeight);
    horizontalOffset = parameterSelectionBounds.getRight() + hspacing;
    parameterSelectionComponent.setBounds(parameterSelectionBounds);
    
    // ROW2
    
    horizontalOffset = rootBounds.getX();
    verticalOffset = rootBounds.getY() + vspacing + rowHeight;
    
    flexWidth = (fullWidth - groupLabelWidth - descriptorLabelWidth - buttonWidth - (hspacing*4)) / 2;
    
    Rectangle<int> groupLabelBounds(horizontalOffset, verticalOffset, groupLabelWidth, rowHeight);
    horizontalOffset = groupLabelBounds.getRight() + hspacing;
    groupLabel.setBounds(groupLabelBounds);
    
    Rectangle<int> groupFieldBounds(horizontalOffset, verticalOffset, flexWidth, rowHeight);
    horizontalOffset = groupFieldBounds.getRight() + hspacing;
    groupField.setBounds(groupFieldBounds);
    
    Rectangle<int> descriptorLabelBounds(horizontalOffset, verticalOffset, descriptorLabelWidth, rowHeight);
    horizontalOffset = descriptorLabelBounds.getRight() + hspacing;
    descriptorLabel.setBounds(descriptorLabelBounds);
    
    Rectangle<int> descriptorFieldBounds(horizontalOffset, verticalOffset, flexWidth, rowHeight);
    horizontalOffset = descriptorFieldBounds.getRight() + hspacing;
    descriptorField.setBounds(descriptorFieldBounds);
    
    
    // BUTTON
    
    horizontalOffset = rootBounds.getX() + fullWidth - buttonWidth;
    verticalOffset = rootBounds.getY();
    
    //int buttonHeight = (rowHeight * 2) + vspacing; // spans two rows
    Rectangle<int> buttonBounds(horizontalOffset, verticalOffset, buttonWidth, rowHeight);
    deleteButton.setBounds(buttonBounds);
    
}

void ParameterRelayComponent::setRelay(std::shared_ptr<Relay> _relay)
{
    std::shared_ptr<ParameterRelay> parameterRelay = std::dynamic_pointer_cast<ParameterRelay>(_relay);
    parameterSelectionComponent.setRelay(parameterRelay);
    RelayComponent::setRelay( _relay );
}


void ParameterRelayComponent::refresh()
{
    RelayComponent::refresh();
    
    std::shared_ptr<ParameterRelay> parameterRelay = std::dynamic_pointer_cast<ParameterRelay>(relay);
    
    if (parameterRelay)
    {
        descriptorField.setText(parameterRelay->getDescriptor(), dontSendNotification);
    }
    else
    {
        descriptorField.setText("", dontSendNotification);
    }
    
    parameterSelectionComponent.refresh();
}

void ParameterRelayComponent::buttonClicked (Button* button)
{
    if (button == &deleteButton)
    {
        if (relay) processor.getParameterRelayManager().deleteItem(relay->getIdentifier());
    }
}


ParameterListComponent::ParameterListComponent(RelayAudioProcessor& _processor) :
    listController("Relay parameter changes to OSC targets"),
    processor(_processor)
{
    processor.getParameterRelayManager().addChangeListener(this);
    
    setOpaque(false);
    
    addAndMakeVisible(listController);
    listController.add(this);
    
    // Create our table component and add it to this component..
    addAndMakeVisible (listBox);
    
    listBox.setOutlineThickness(0);
    listBox.setRowHeight(ParameterRelayComponent::desiredHeight + 10);
    
    listBox.setOpaque(false);
    listBox.setColour(ListBox::ColourIds::backgroundColourId, Colours::transparentBlack);
    
    listBox.setModel (this);
}


void ParameterListComponent::resized()
{
    int controllerHeight = 45;
    int hmargin = 4;
    int vmargin = 4;
    int vspacing = 4;
    
    Rectangle<int> rootBounds = getBounds();
    int verticalOffset = vmargin;
    int width = rootBounds.getWidth();
    
    int listHeight = rootBounds.getHeight() - controllerHeight;
    
    listBox.setBounds( Rectangle<int>(hmargin, vmargin, width, listHeight) );
    verticalOffset = listBox.getBottom() + vspacing;
    
    listController.setBounds( Rectangle<int>(0, verticalOffset, width, controllerHeight) );
}

void ParameterListComponent::changeListenerCallback (ChangeBroadcaster *source)
{
    // if the targets change then we need to update the table so that the new targets are available
    if (source == dynamic_cast<ChangeBroadcaster*>(&(processor.getParameterRelayManager())))
    {
        std::cout << "ParameterListComponent updating table content on targetManager change\n";
        listBox.updateContent();
    }
}

void ParameterListComponent::newItemRequest(Component* sender)
{
    processor.getParameterRelayManager().newItem();
    listBox.updateContent();
}

void ParameterListComponent::clearItemsRequest(Component* sender)
{
    processor.getParameterRelayManager().clear();
    listBox.updateContent();
}

int ParameterListComponent::getNumRows()
{
    return processor.getParameterRelayManager().getItems().size();
}

void ParameterListComponent::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
    
}

Component* ParameterListComponent::refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate)
{
    ParameterRelayComponent* relayComponent = static_cast<ParameterRelayComponent*> (existingComponentToUpdate);
    
    std::shared_ptr<ParameterRelay> relay = nullptr;
    
    if (rowNumber < processor.getParameterRelayManager().count())
    {
        relay = processor.getParameterRelayManager().getItem(rowNumber);
    }
    
    // If an existing component is being passed-in for updating, we'll re-use it, if not, we'll have to create one.
    if (relayComponent == nullptr)
    {
        relayComponent = new ParameterRelayComponent(processor);
    }
    
    relayComponent->setRelay(relay);
    return relayComponent;
}

