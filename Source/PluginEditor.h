/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "PluginProcessor.h"

#include "OSCTargetManager.h"
#include "MIDIRelay.h"
#include "ParameterRelay.h"

#include "TargetComponent.h"
#include "MIDIComponent.h"
#include "ParameterComponent.h"
#include "TestComponent.h"


class MainTabbedComponent  : public TabbedComponent
{
    
public:
    
    MainTabbedComponent(RelayAudioProcessor& processor);
    
private:
    
    RelayAudioProcessor& processor;
    
    TargetComponent targetComponent;
    MIDIComponent midiComponent;
    ParameterComponent parameterComponent;
    TestComponent testComponent;
};


class RelayAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    RelayAudioProcessorEditor (RelayAudioProcessor&);
    ~RelayAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    RelayAudioProcessor& processor;
    
    MainTabbedComponent tabbedComponent;
    
    ScopedPointer<ResizableCornerComponent> resizer;
    ComponentBoundsConstrainer resizeLimits;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RelayAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
