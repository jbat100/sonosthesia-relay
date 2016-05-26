/*
  ==============================================================================

    TargetListComponent.h
    Created: 26 May 2016 3:00:51pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef TARGETLISTCOMPONENT_H_INCLUDED
#define TARGETLISTCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class TargetListComponent    : public Component
{
public:
    TargetListComponent();
    ~TargetListComponent();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TargetListComponent)
};


#endif  // TARGETLISTCOMPONENT_H_INCLUDED
