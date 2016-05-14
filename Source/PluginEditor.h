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
#include "MIDIRelayManager.h"
#include "ParameterRelayManager.h"

#include "TargetComponent.h"
#include "MIDIComponent.h"
#include "ParameterComponent.h"


class MainTabbedComponent  : public TabbedComponent
{
    
public:
    MainTabbedComponent(OSCTargetManager& oscTargetManager,
                        MIDIRelayManager& midiRelayManager,
                        ParameterRelayManager& parameterRelayManager);
    
private:
    
    TargetComponent targetComponent;
    MIDIComponent midiComponent;
    ParameterComponent parameterComponent;
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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RelayAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
