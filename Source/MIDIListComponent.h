/*
  ==============================================================================

    MIDIListComponent.h
    Created: 26 May 2016 2:59:59pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef MIDILISTCOMPONENT_H_INCLUDED
#define MIDILISTCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MIDIListComponent    : public Component
{
public:
    MIDIListComponent();
    ~MIDIListComponent();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MIDIListComponent)
};


#endif  // MIDILISTCOMPONENT_H_INCLUDED
