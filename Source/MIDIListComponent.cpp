/*
  ==============================================================================

    MIDIListComponent.cpp
    Created: 26 May 2016 2:59:59pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MIDIListComponent.h"


void MIDIRelayComponent::setMIDIRelay(std::shared_ptr<MIDIRelay> _relay)
{
    
}

std::shared_ptr<MIDIRelay> MIDIRelayComponent::getMIDIRelay()
{
    return nullptr;
}

void MIDIRelayComponent::refresh()
{
    
}

void MIDIRelayComponent::labelTextChanged(Label *label)
{
    
}

void MIDIRelayComponent::buttonClicked (Button* button)
{
    
}


MIDIListComponent::MIDIListComponent(MIDIRelayManager& _relayManager, OSCTargetManager& _targetManager) :
    targetManager(_targetManager),
    relayManager(_relayManager)
{
    
}

void MIDIListComponent::paint (Graphics&)
{
    
}

void MIDIListComponent::resized()
{
    
}

void MIDIListComponent::changeListenerCallback (ChangeBroadcaster *source)
{
    
}

void MIDIListComponent::buttonClicked (Button* button)
{
    
}

int MIDIListComponent::getNumRows()
{
    
}

void MIDIListComponent::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
    
}

Component* MIDIListComponent::refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate)
{
    
}

