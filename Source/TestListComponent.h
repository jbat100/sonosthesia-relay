/*
  ==============================================================================

    TestListComponent.h
    Created: 26 May 2016 3:03:15pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef TESTLISTCOMPONENT_H_INCLUDED
#define TESTLISTCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class TestListComponent    : public Component
{
public:
    TestListComponent();
    ~TestListComponent();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestListComponent)
};


#endif  // TESTLISTCOMPONENT_H_INCLUDED
