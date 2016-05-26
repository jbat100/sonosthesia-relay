/*
  ==============================================================================

    TargetListComponent.cpp
    Created: 26 May 2016 3:00:51pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TargetListComponent.h"


TargetComponent::TargetComponent(OSCTargetManager& _manager, std::shared_ptr<OSCTarget> _target) :
    manager(_manager),
    target(_target)
{
    jassert(_target);
    target->add(this);
    
    addAndMakeVisible(hostLabel);
    
    addAndMakeVisible(hostField);
    hostField.setEditable(false, true, false);
    hostField.setColour(Label::textColourId, Colours::black);
    hostField.addListener(this);
    
    addAndMakeVisible(portLabel);
    
    addAndMakeVisible(portField);
    portField.setEditable(false, true, false);
    portField.setColour(Label::textColourId, Colours::black);
    portField.addListener(this);
    
    addAndMakeVisible(statusLabel);
    
    addAndMakeVisible(deleteButton);
    deleteButton.addListener(this);
    
}

void TargetComponent::paint (Graphics& g)
{

    g.fillAll (Colours::grey);   // clear the background
    
    g.setColour (Colours::white);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
}

/*

void TargetComponent::resized()
{
    
    int margin = 4;
    int labelWidth = 100;
    int buttonWidth = 200;
    int labelHeight = 30;
    
    Rectangle<int> rootBounds = getBounds().reduced(margin*2, margin*2).translated(margin, margin);
    
    int fullWidth = rootBounds.getWidth();
    //int fullHeight = rootBounds.getHeight();
    
    // labels are on the right
    Rectangle<int> labelBounds = rootBounds.withWidth(labelWidth);
    int labelMargin = 2;
    Rectangle<int> hostnameLabelBounds = labelBounds.withHeight(labelHeight).reduced(labelMargin, labelMargin);
    
    // fields are in the middle, and will stretch with width
    Rectangle<int> fieldBounds = rootBounds.translated(labelWidth, 0).withWidth(fullWidth - labelWidth - buttonWidth);
    
    // fields are in the middle, and will stretch with width
    Rectangle<int> buttonBounds = rootBounds.translated(fullWidth - buttonWidth, 0).withWidth(buttonWidth);
    
    
}
 
 */

void TargetComponent::resized()
{
    
    int margin = 4;
    int spacing = 4;
    
    int hostLabelWidth = 100;
    //int hostFieldWidth = 200; // hostname field will resize proportionally
    int portLabelWidth = 50;
    int portFieldWidth = 50;
    
    int statusLabelWidth = 200;
    
    int labelHeight = 30;
    int buttonWidth = 60;
    int buttonHeight = 30;
    
    Rectangle<int> rootBounds = getBounds().reduced(margin*2, margin*2).translated(margin, margin);
    
    int fullWidth = rootBounds.getWidth();
    //int fullHeight = rootBounds.getHeight();
    int horizontalOffset = rootBounds.getX();
    
    Rectangle<int> hostLabelBounds = rootBounds.withX(horizontalOffset).withWidth(hostLabelWidth).withHeight(labelHeight);
    horizontalOffset = hostLabelBounds.getRight() + spacing;
    hostLabel.setBounds(hostLabelBounds);

    int hostFieldWidth = fullWidth - hostLabelWidth - portLabelWidth - portFieldWidth - buttonWidth - (spacing*4);
    Rectangle<int> hostFieldBounds = rootBounds.withX(horizontalOffset).withWidth(hostFieldWidth).withHeight(labelHeight);
    horizontalOffset = hostFieldBounds.getRight() + spacing;
    hostField.setBounds(hostFieldBounds);
    
    Rectangle<int> portLabelBounds = rootBounds.withX(horizontalOffset).withWidth(portLabelWidth).withHeight(labelHeight);
    horizontalOffset = portLabelBounds.getRight() + spacing;
    portLabel.setBounds(portLabelBounds);
    
    Rectangle<int> portFieldBounds = rootBounds.withX(horizontalOffset).withWidth(portFieldWidth).withHeight(labelHeight);
    horizontalOffset = portFieldBounds.getRight() + spacing;
    portField.setBounds(portLabelBounds);
    
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
    target = nullptr;
}

void TargetComponent::refresh()
{
    if (target)
    {
        hostField.setText(target->getHostName(), dontSendNotification);
        portField.setText(String(target->getPortNumber()), dontSendNotification);
        statusLabel.setText(target->isConnected() ? "Connected" : "Disconnected", dontSendNotification);
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

}

TargetListComponent::~TargetListComponent()
{
}

void TargetListComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::grey);   // clear the background

    g.setColour (Colours::white);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

}

void TargetListComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void TargetListComponent::buttonClicked (Button* button)
{
    
}

int TargetListComponent::getNumRows()
{
    return 0;
}
void TargetListComponent::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
    
}

Component* TargetListComponent::refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate)
{
    return nullptr;
}
