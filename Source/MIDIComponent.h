/*
  ==============================================================================

    MIDIComponent.h
    Created: 12 May 2016 4:38:11pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef MIDICOMPONENT_H_INCLUDED
#define MIDICOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "MIDIRelayManager.h"

//==============================================================================
/*
*/
class MIDIComponent    : public Component
{
public:
    MIDIComponent(MIDIRelayManager& _midiRelayManager);
    ~MIDIComponent();

    void paint (Graphics&);
    void resized();

private:
    
    MIDIRelayManager& midiRelayManager;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MIDIComponent)
};


#endif  // MIDICOMPONENT_H_INCLUDED
