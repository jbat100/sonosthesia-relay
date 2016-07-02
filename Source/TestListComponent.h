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

#include "CommonComponent.h"
#include "PluginProcessor.h"


class ParameterTestComponent : public Component {
    
public:
    
    ParameterTestComponent(AudioProcessorParameter& _parameter);
    
    virtual ~ParameterTestComponent() {};
    
    void paint (Graphics& g) override;
    void resized() override;
    
    static const int desiredHeight;
    static const int hmargin;
    
private:
    
    Label nameLabel;
    
    ParameterSlider slider;
    
    AudioProcessorParameter& parameter;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterTestComponent)
};

//==============================================================================
/*
*/
class TestListComponent : public Component, public ListBoxModel
{
public:
    TestListComponent(RelayAudioProcessor& _processor);
    ~TestListComponent();
    
    void paint (Graphics&) override;
    void resized() override;
    
    void update();
    
    // ======== ListBoxModel ===========
    
    int getNumRows() override;
    void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) override;
    
private:
    
    ListBox listBox;
    Font font;
    
    RelayAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestListComponent)
};


#endif  // TESTLISTCOMPONENT_H_INCLUDED
