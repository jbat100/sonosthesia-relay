/*
  ==============================================================================

    TargetComponent.cpp
    Created: 12 May 2016 4:37:10pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TargetComponent.h"

//==============================================================================
TargetComponent::TargetComponent(OSCTargetManager& _oscTargetManager) : oscTargetManager(_oscTargetManager)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    addAndMakeVisible(newButton);
    
    newButton.addListener(this);
    newButton.setButtonText("New");

}

TargetComponent::~TargetComponent()
{
}

void TargetComponent::paint (Graphics& g)
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
    // g.drawText ("TargetComponent", getLocalBounds(), Justification::centred, true);
}

void TargetComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains...
    
    Rectangle<int> b = getBounds().withX(0).withY(0).withHeight(20).reduced(4);
    
    //b.setHeight(20);
    //b.reduce(<#int deltaX#>, <#int deltaY#>)
    
    newButton.setBounds( b );
}

void TargetComponent::buttonClicked (Button* button)
{
    if (button == &newButton)
    {
        std::cout << "Make new target!\n";
    }
}
