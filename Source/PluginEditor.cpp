/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


MainTabbedComponent::MainTabbedComponent(OSCTargetManager& oscTargetManager,
                                         MIDIRelayManager& midiRelayManager,
                                         ParameterRelayManager& parameterRelayManager) :
TabbedComponent (TabbedButtonBar::TabsAtTop),
targetComponent(oscTargetManager),
midiComponent(midiRelayManager),
parameterComponent(parameterRelayManager)
{
    Colour colour = Colours::black;
    
    addTab ("MIDI", Colours::white, &midiComponent, true);
    addTab ("Parameters", Colours::white, &parameterComponent, true);
    addTab ("Targets", Colours::white, &targetComponent, true);

}

//==============================================================================
RelayAudioProcessorEditor::RelayAudioProcessorEditor (RelayAudioProcessor& p) :
AudioProcessorEditor (&p),
processor (p),
tabbedComponent(p.getOSCTargetManager(), p.getMIDIRelayManager(), p.getParameterRelayManager())
{
    setOpaque (true);
    addAndMakeVisible(&tabbedComponent);
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

RelayAudioProcessorEditor::~RelayAudioProcessorEditor()
{
}

//==============================================================================
void RelayAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::black);
    g.setColour (Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void RelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    //tabbedComponent.setBounds (getLocalBounds().reduced (4));
    tabbedComponent.setBounds (getLocalBounds());
}
