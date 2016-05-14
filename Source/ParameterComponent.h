/*
  ==============================================================================

    ParameterComponent.h
    Created: 12 May 2016 4:37:39pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef PARAMETERCOMPONENT_H_INCLUDED
#define PARAMETERCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "ParameterRelayManager.h"

//==============================================================================
/*
*/
class ParameterComponent    : public Component
{
public:
    ParameterComponent(ParameterRelayManager& _parameterRelayManager);
    ~ParameterComponent();

    void paint (Graphics&);
    void resized();

private:
    
    ParameterRelayManager& parameterRelayManager;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterComponent)
};


#endif  // PARAMETERCOMPONENT_H_INCLUDED
