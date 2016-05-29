/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


MainTabbedComponent::MainTabbedComponent(RelayAudioProcessor& _processor) :
    TabbedComponent (TabbedButtonBar::TabsAtTop),
    processor(_processor),
    targetComponent(processor.getOSCTargetManager()),
    midiComponent(processor.getMIDIRelayManager(), processor.getOSCTargetManager()),
    parameterComponent(processor),
    testComponent(processor)
{
    File applicationFile = File::getSpecialLocation(File::SpecialLocationType::currentApplicationFile);
    std::cout << "Plugin path : " << applicationFile.getFullPathName() << "\n";
    
    Colour colour = Colours::transparentBlack; // Colour(Colours::black).withAlpha(0.0f);
    
    addTab ("MIDI", colour, &midiComponent, true);
    addTab ("Parameters", colour, &parameterComponent, true);
    addTab ("Targets", colour, &targetComponent, true);
    addTab ("Test", colour, &testComponent, true);

}

//==============================================================================
RelayAudioProcessorEditor::RelayAudioProcessorEditor (RelayAudioProcessor& p) :
    AudioProcessorEditor (&p),
    processor (p),
    tabbedComponent(p)
{
    setOpaque (true);

    
    addAndMakeVisible(&tabbedComponent);

    addAndMakeVisible (resizer = new ResizableCornerComponent (this, &resizeLimits));
    resizeLimits.setSizeLimits (150, 150, 1000, 500);
    
    std::cout << "Editor setting UI dimensions to processor setting " << processor.lastUIWidth << " " << processor.lastUIHeight << "\n";
    
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (processor.lastUIWidth, processor.lastUIHeight);
}

RelayAudioProcessorEditor::~RelayAudioProcessorEditor()
{
}

//==============================================================================
void RelayAudioProcessorEditor::paint (Graphics& g)
{
    //g.fillAll (Colours::black);
    //g.setColour (Colours::black);
    
    
    //File file = File::getCurrentWorkingDirectory().getChildFile ("partial or full path");
    
    File applicationFile = File::getSpecialLocation(File::SpecialLocationType::currentApplicationFile);
    
    File imageFile = applicationFile.getChildFile("Contents/Resources/space-dense.png");
    
    Image image = ImageCache::getFromFile(imageFile);
    
    g.setTiledImageFill (image, 0, 0, 1.0);
    
    g.fillAll();
}

void RelayAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    //tabbedComponent.setBounds (getLocalBounds().reduced (4));
    tabbedComponent.setBounds (getLocalBounds());
    
    resizer->setBounds (getWidth() - 16, getHeight() - 16, 16, 16);
    
    processor.lastUIWidth = getWidth();
    processor.lastUIHeight = getHeight();
}
