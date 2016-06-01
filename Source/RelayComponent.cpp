/*
  ==============================================================================

    RelayComponent.cpp
    Created: 16 May 2016 4:07:30pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "RelayComponent.h"
#include "Theme.h"

RelayComponent::RelayComponent(OSCTargetManager& _targetManager) :
    targetManager(_targetManager),
    targetSelectionComponent(_targetManager)
{
    setOpaque(false);
    
    addAndMakeVisible(groupLabel);
    groupLabel.setText("Group", dontSendNotification);
    Appearence::theme()->label(groupLabel);
    
    addAndMakeVisible(groupField);
    groupField.setEditable(false, true, false);
    groupField.addListener(this);
    Appearence::theme()->field(groupField);
    
    addAndMakeVisible(deleteButton);
    deleteButton.addListener(this);
    deleteButton.setButtonText("Delete");
    Appearence::theme()->textButton(deleteButton);
}

void RelayComponent::setRelay(std::shared_ptr<Relay> _relay)
{
    targetSelectionComponent.setRelay(_relay);
    relay = _relay;
    refresh();
}

void RelayComponent::refresh()
{
    if (relay)
    {
        groupField.setText(relay->getGroup(), dontSendNotification);
    }
    else
    {
        groupField.setText("", dontSendNotification);
    }
    
    targetSelectionComponent.refresh();
}

void RelayComponent::labelTextChanged(Label *label)
{
    if (label == &groupField)
    {
        if (relay) relay->setGroup(groupField.getText());
    }
}

void RelayComponent::buttonClicked (Button* button)
{
    
}
