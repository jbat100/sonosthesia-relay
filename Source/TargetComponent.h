/*
  ==============================================================================

    TargetComponent.h
    Created: 12 May 2016 4:37:10pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef TARGETCOMPONENT_H_INCLUDED
#define TARGETCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "OSCTargetManager.h"

//==============================================================================
/*
*/
class TargetComponent    : public Component, public Button::Listener
{
public:
    TargetComponent(OSCTargetManager& _oscTargetManager);
    ~TargetComponent();

    void paint (Graphics&);
    void resized();
    
    void buttonClicked (Button* button);

private:
    
    TextButton newButton;
    
    OSCTargetManager& oscTargetManager;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TargetComponent)
};


#endif  // TARGETCOMPONENT_H_INCLUDED
