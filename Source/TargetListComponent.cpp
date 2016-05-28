/*
  ==============================================================================

    TargetListComponent.cpp
    Created: 26 May 2016 3:00:51pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TargetListComponent.h"
#include "Theme.h"

const int TargetComponent::desiredHeight = 50;

TargetComponent::TargetComponent(OSCTargetManager& _manager) : manager(_manager), target(nullptr)
{
    Colour labelTextColour = Colours::whitesmoke;
    
    addAndMakeVisible(hostLabel);
    hostLabel.setText("Host", dontSendNotification);
    Appearence::theme()->label(hostLabel);
    
    addAndMakeVisible(hostField);
    hostField.setEditable(false, true, false);
    hostField.addListener(this);
    Appearence::theme()->field(hostField);
    
    addAndMakeVisible(portLabel);
    portLabel.setText("Port", dontSendNotification);
    Appearence::theme()->label(portLabel);
    
    addAndMakeVisible(portField);
    portField.setEditable(false, true, false);
    portField.addListener(this);
    Appearence::theme()->field(portField);
    
    addAndMakeVisible(statusLabel);
    Appearence::theme()->indicator(statusLabel, Theme::Level::Warning);
    
    addAndMakeVisible(deleteButton);
    deleteButton.addListener(this);
    deleteButton.setButtonText("Delete");
    Appearence::theme()->textButton(deleteButton);
    
}

void TargetComponent::setTarget(std::shared_ptr<OSCTarget> _target)
{
    if (target)
    {
        target->remove(this);
    }
    
    target = _target;
    
    if (target)
    {
        target->add(this);
    }
    
    refresh();
}

void TargetComponent::paint (Graphics& g)
{

    g.fillAll (Colours::grey);   // clear the background
    
    g.setColour (Colours::white);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
}

void TargetComponent::resized()
{
    int vmargin = 4;
    int hmargin = 10;
    int spacing = 10;
    
    int hostLabelWidth = 40;
    //int hostFieldWidth = 200; // hostname field will resize proportionally
    int portLabelWidth = 40;
    int portFieldWidth = 50;
    
    int statusLabelWidth = 100;
    
    int labelHeight = 20;
    int buttonWidth = 60;
    int buttonHeight = 20;
    
    Rectangle<int> bounds = getBounds();
    
    
    Rectangle<int> rootBounds = getBounds().reduced(hmargin*2, vmargin*2).translated(hmargin, vmargin);
    
    int fullWidth = rootBounds.getWidth();
    //int fullHeight = rootBounds.getHeight();
    int horizontalOffset = rootBounds.getX();
    
    Rectangle<int> hostLabelBounds = rootBounds.withX(horizontalOffset).withWidth(hostLabelWidth).withHeight(labelHeight);
    horizontalOffset = hostLabelBounds.getRight() + spacing;
    hostLabel.setBounds(hostLabelBounds);

    int hostFieldWidth = fullWidth - hostLabelWidth - portLabelWidth - portFieldWidth - buttonWidth - statusLabelWidth - (spacing*5);
    Rectangle<int> hostFieldBounds = rootBounds.withX(horizontalOffset).withWidth(hostFieldWidth).withHeight(labelHeight);
    horizontalOffset = hostFieldBounds.getRight() + spacing;
    hostField.setBounds(hostFieldBounds);
    
    Rectangle<int> portLabelBounds = rootBounds.withX(horizontalOffset).withWidth(portLabelWidth).withHeight(labelHeight);
    horizontalOffset = portLabelBounds.getRight() + spacing;
    portLabel.setBounds(portLabelBounds);
    
    Rectangle<int> portFieldBounds = rootBounds.withX(horizontalOffset).withWidth(portFieldWidth).withHeight(labelHeight);
    horizontalOffset = portFieldBounds.getRight() + spacing;
    portField.setBounds(portFieldBounds);
    
    Rectangle<int> statusLabelBounds = rootBounds.withX(horizontalOffset).withWidth(statusLabelWidth).withHeight(labelHeight);
    horizontalOffset = statusLabelBounds.getRight() + spacing;
    statusLabel.setBounds(statusLabelBounds);
    
    Rectangle<int> deleteButtonBounds = rootBounds.withX(horizontalOffset).withWidth(buttonWidth).withHeight(buttonHeight);
    horizontalOffset = deleteButtonBounds.getRight() + spacing;
    deleteButton.setBounds(deleteButtonBounds);
    
}

void TargetComponent::buttonClicked (Button* button)
{
    if (button == &deleteButton)
    {
        if (target) manager.deleteItem(target->getIdentifier());
    }
}

void TargetComponent::labelTextChanged(Label *label)
{
    if (!target) return;
    
    if (label == &hostField)
    {
         target->setHostName(label->getText());
    }
    else if (label == &portField)
    {
        int port = label->getText().getIntValue();
        
        if (port > 0)
        {
            target->setPortNumber(port);
        }
        else
        {
            refresh(); // sets the field back to its current valid value
        }
    }
    
}

void TargetComponent::targetInvalidated(OSCTarget* _target)
{
    if (target.get() == _target)
    {
        setTarget(nullptr);
    }
}

void TargetComponent::refresh()
{
    if (target)
    {
        hostField.setText(target->getHostName(), dontSendNotification);
        portField.setText(String(target->getPortNumber()), dontSendNotification);
        
        statusLabel.setText(target->isConnected() ? "Connected" : "Disconnected", dontSendNotification);
        Appearence::theme()->indicator(statusLabel, target->isConnected() ? Theme::Level::Primary : Theme::Level::Warning);
    }
    else
    {
        hostField.setText("", dontSendNotification);
        portField.setText("", dontSendNotification);
        statusLabel.setText("", dontSendNotification);
    }
}

//==============================================================================
TargetListComponent::TargetListComponent(OSCTargetManager& _oscTargetManager) : oscTargetManager(_oscTargetManager)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    
    addAndMakeVisible(newButton);
    newButton.addListener(this);
    newButton.setButtonText("New");
    
    addAndMakeVisible(clearButton);
    clearButton.addListener(this);
    clearButton.setButtonText("Clear");
    
    // Create our table component and add it to this component..
    addAndMakeVisible (listBox);
    
    listBox.setOutlineThickness(0);
    listBox.setRowHeight(TargetComponent::desiredHeight);
    listBox.setOpaque(false);
    
    listBox.setModel (this);
    
    
    oscTargetManager.addChangeListener(this);
        
}

TargetListComponent::~TargetListComponent()
{
}

void TargetListComponent::paint (Graphics& g)
{


}

void TargetListComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    // This method is where you should set the bounds of any child
    // components that your component contains...
    
    int buttonHeight = 25;
    int margin = 4;
    
    Rectangle<int> bounds = getBounds();
    
    int halfWidth = bounds.getWidth() / 2;
    
    newButton.setBounds( getBounds().withX(0).withY(0).withHeight(buttonHeight).withWidth(halfWidth).reduced(margin) );
    clearButton.setBounds( getBounds().withX(halfWidth).withY(0).withHeight(buttonHeight).withWidth(halfWidth).reduced(margin) );
    
    listBox.setBounds( getBounds().withX(0).withY(buttonHeight).withTrimmedBottom(buttonHeight).reduced(margin) );
    
}

void TargetListComponent::buttonClicked (Button* button)
{
    if (button == &newButton)
    {
        //std::cout << "Make new target!\n";
        oscTargetManager.newItem();
        listBox.updateContent();
    }
    else if (button == &clearButton)
    {
        //std::cout << "Clear targets!\n";
        oscTargetManager.invalidateAll();
        oscTargetManager.clear();
        listBox.updateContent();
    }
}

int TargetListComponent::getNumRows()
{
    return oscTargetManager.count();
}

void TargetListComponent::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
    g.setColour(Colours::black);
    
    g.drawRoundedRectangle(0, 0, width, height, 5, 2);
}

Component* TargetListComponent::refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate)
{
    TargetComponent* targetComponent = static_cast<TargetComponent*> (existingComponentToUpdate);
    
    std::shared_ptr<OSCTarget> target = nullptr;
    
    if (rowNumber < oscTargetManager.count())
    {
        target = oscTargetManager.getItem(rowNumber);
    }
    
    // If an existing component is being passed-in for updating, we'll re-use it, but
    // if not, we'll have to create one.
    if (targetComponent == nullptr)
    {
        targetComponent = new TargetComponent(oscTargetManager);
    }
    
    targetComponent->setTarget(target);
    return targetComponent;
}

void TargetListComponent::changeListenerCallback (ChangeBroadcaster *source)
{
    // if the targets change then we need to update the table so that the new targets are available
    if (source == dynamic_cast<ChangeBroadcaster*>(&oscTargetManager))
    {
        listBox.updateContent();
    }
}
