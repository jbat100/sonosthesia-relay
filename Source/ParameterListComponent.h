/*
  ==============================================================================

    ParameterListComponent.h
    Created: 26 May 2016 3:00:19pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef PARAMETERLISTCOMPONENT_H_INCLUDED
#define PARAMETERLISTCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class ParameterListComponent    : public Component
{
public:
    ParameterListComponent();
    ~ParameterListComponent();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterListComponent)
};


#endif  // PARAMETERLISTCOMPONENT_H_INCLUDED
