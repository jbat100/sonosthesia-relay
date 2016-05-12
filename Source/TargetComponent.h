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

//==============================================================================
/*
*/
class TargetComponent    : public Component
{
public:
    TargetComponent();
    ~TargetComponent();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TargetComponent)
};


#endif  // TARGETCOMPONENT_H_INCLUDED
