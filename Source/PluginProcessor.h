/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#define COMP_TYPE		kAudioUnitComponentType
#define COMP_SUBTYPE	kAudioUnitOutputSubType
#define COMP_MANUF		kAudioUnitAudioHardwareOutputSubSubType


#include "../JuceLibraryCode/JuceHeader.h"
#include "OSCTargetManager.h"
#include "MidiRelay.h"
#include "ParameterRelay.h"


//==============================================================================
/**
*/
class RelayAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    RelayAudioProcessor();
    ~RelayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet) override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    //==============================================================================
    OSCTargetManager& getOSCTargetManager();
    MIDIRelayManager& getMIDIRelayManager();
    ParameterRelayManager& getParameterRelayManager();
    
    // these are used to persist the UI's size - the values are stored along with the
    // filter's other parameters, and the UI component will update them when it gets
    // resized.
    int lastUIWidth, lastUIHeight;
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RelayAudioProcessor)
    
    OSCTargetManager oscTargetManager;
    MIDIRelayManager midiRelayManager;
    ParameterRelayManager parameterRelayManager;
    
    // state set/get helpers
    
    void saveOSCTarget(std::shared_ptr<OSCTarget> target, XmlElement* element);
    std::shared_ptr<OSCTarget> loadOSCTarget(XmlElement* element);
    
    void saveMIDIRelay(std::shared_ptr<MIDIRelay> relay, XmlElement* element);
    std::shared_ptr<MIDIRelay> loadMIDIRelay(XmlElement* element);
    
    void saveParameterRelay(std::shared_ptr<ParameterRelay> relay, XmlElement* element);
    std::shared_ptr<ParameterRelay> loadParameterRelay(XmlElement* element);
    
    std::shared_ptr<OSCTarget> getTargetForElement(XmlElement* element);
    
    static int parameterCount;
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
