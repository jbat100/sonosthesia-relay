/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

int RelayAudioProcessor::parameterCount = 10;

//==============================================================================

RelayAudioProcessor::RelayAudioProcessor() : lastUIWidth(600), lastUIHeight(300), parameterRelayManager(*this)
{
    for (int i = 1; i <= parameterCount; i++)
    {
        // note that "0", "1" etc are not valid xml names according to juice and so they are undesirable as parameter ids
        addParameter(new AudioParameterFloat (String("Parameter") + String(i),  String("Parameter") + String(i), 0.0f, 1.0f, 0.0f));
    }
}

RelayAudioProcessor::~RelayAudioProcessor()
{
}

//==============================================================================

const String RelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool RelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool RelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double RelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int RelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int RelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void RelayAudioProcessor::setCurrentProgram (int index)
{
}

const String RelayAudioProcessor::getProgramName (int index)
{
    return String();
}

void RelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================

void RelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void RelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool RelayAudioProcessor::setPreferredBusArrangement (bool isInput, int bus, const AudioChannelSet& preferredSet)
{
    // Reject any bus arrangements that are not compatible with your plugin

    const int numChannels = preferredSet.size();

   #if JucePlugin_IsMidiEffect
    if (numChannels != 0)
        return false;
   #elif JucePlugin_IsSynth
    if (isInput || (numChannels != 1 && numChannels != 2))
        return false;
   #else
    if (numChannels != 1 && numChannels != 2)
        return false;

    if (! AudioProcessor::setPreferredBusArrangement (! isInput, bus, preferredSet))
        return false;
   #endif

    return AudioProcessor::setPreferredBusArrangement (isInput, bus, preferredSet);
}
#endif

void RelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        //float* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    
    int time;
    MidiMessage m;
    
    auto items = midiRelayManager.getItems();
    
    for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
    {
        for (auto i = items.begin(); i != items.end(); i++)
        {
            (*i)->relay(m);
        }
    }
    
    parameterRelayManager.refresh();

}

//==============================================================================

bool RelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* RelayAudioProcessor::createEditor()
{
    return new RelayAudioProcessorEditor (*this);
}

//==============================================================================

void RelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // Here's an example of how you can use XML to make it easy and more robust:
    
    std::cout << "Processor storing state\n";
    
    // Create an outer XML element..
    XmlElement xml ("sonosthesia_relay_settings");
    
    // add some attributes to it..
    xml.setAttribute ("ui_width", lastUIWidth);
    xml.setAttribute ("ui_height", lastUIHeight);
    
    // Store the values of all our parameters, using their param ID as the XML attribute
    for (int i = 0; i < getNumParameters(); ++i)
        if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
            xml.setAttribute (p->paramID, p->getValue());
    
    // Store targets...
    XmlElement* targetsElement = xml.createNewChildElement("targets");
    auto targets = oscTargetManager.getItems();
    for (auto i = targets.begin(); i != targets.end(); i++)
    {
        XmlElement* targetElement = targetsElement->createNewChildElement("target");
        saveOSCTarget((*i), targetElement);
    }
    
    // Store midi relays...
    XmlElement* midiRelaysElement = xml.createNewChildElement("midi_relays");
    auto midiRelays = midiRelayManager.getItems();
    for (auto i = midiRelays.begin(); i != midiRelays.end(); i++)
    {
        XmlElement* midiRelayElement = midiRelaysElement->createNewChildElement("midi_relay");
        saveMIDIRelay((*i), midiRelayElement);
    }
    
    // Store parameter relays...
    XmlElement* parameterRelaysElement = xml.createNewChildElement("parameter_relays");
    auto parameterRelays = parameterRelayManager.getItems();
    for (auto i = parameterRelays.begin(); i != parameterRelays.end(); i++)
    {
        XmlElement* parameterRelayElement = parameterRelaysElement->createNewChildElement("parameter_relay");
        saveParameterRelay((*i), parameterRelayElement);
    }
    
    // then use this helper function to stuff it into the binary blob and return it..
    copyXmlToBinary (xml, destData);
}

void RelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    // This getXmlFromBinary() helper function retrieves our XML from the binary blob..
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    std::cout << "Processor restoring from stored state\n";
    
    if (xmlState != nullptr)
    {
        // make sure that it's actually our type of XML object..
        if (xmlState->hasTagName ("sonosthesia_relay_settings"))
        {
            // ok, now pull out our last window size..
            lastUIWidth  = xmlState->getIntAttribute ("ui_width", lastUIWidth);
            lastUIHeight = xmlState->getIntAttribute ("ui_height", lastUIHeight);
            
            std::cout << "Got UI dimensions from stored state " << lastUIWidth << " " << lastUIHeight << "\n";
            
            // Now reload our parameters..
            for (int i = 0; i < getNumParameters(); ++i)
                if (AudioProcessorParameterWithID* p = dynamic_cast<AudioProcessorParameterWithID*> (getParameters().getUnchecked(i)))
                    p->setValueNotifyingHost ((float) xmlState->getDoubleAttribute (p->paramID, p->getValue()));
            
            // order is important, targets must be loaded first, as the relays will need them
            XmlElement* targetsElement = xmlState->getChildByName("targets");
            if (targetsElement)
            {
                for (int i = 0; i < targetsElement->getNumChildElements(); i++)
                {
                    XmlElement* targetElement = targetsElement->getChildElement(i);
                    auto target = loadOSCTarget(targetElement);
                    oscTargetManager.addItem(target);
                }
            }
            
            // load midi relays
            XmlElement* midiRelaysElement = xmlState->getChildByName("midi_relays");
            if (midiRelaysElement)
            {
                for (int i = 0; i < midiRelaysElement->getNumChildElements(); i++)
                {
                    XmlElement* midiRelayElement = midiRelaysElement->getChildElement(i);
                    auto midiRelay = loadMIDIRelay(midiRelayElement);
                    midiRelayManager.addItem(midiRelay);
                }
            }
            
            // load parameter relays
            XmlElement* parameterRelaysElement = xmlState->getChildByName("parameter_relays");
            if (parameterRelaysElement)
            {
                for (int i = 0; i < parameterRelaysElement->getNumChildElements(); i++)
                {
                    XmlElement* parameterRelayElement = parameterRelaysElement->getChildElement(i);
                    auto parameterRelay = loadParameterRelay(parameterRelayElement);
                    parameterRelayManager.addItem(parameterRelay);
                }
            }
        }
    }
}

//==============================================================================

OSCTargetManager& RelayAudioProcessor::getOSCTargetManager()
{
    return oscTargetManager;
}

MIDIRelayManager& RelayAudioProcessor::getMIDIRelayManager()
{
    return midiRelayManager;
}

ParameterRelayManager& RelayAudioProcessor::getParameterRelayManager()
{
    return parameterRelayManager;
}


//==============================================================================

void RelayAudioProcessor::saveOSCTarget(std::shared_ptr<OSCTarget> target, XmlElement* element)
{
    element->setAttribute("identifier", target->getIdentifier());
    element->setAttribute("hostname", target->getHostName());
    element->setAttribute("portnumber", target->getPortNumber());
}

std::shared_ptr<OSCTarget> RelayAudioProcessor::loadOSCTarget(XmlElement* element)
{
    String identifier = element->getStringAttribute("identifier");
    String hostName = element->getStringAttribute("hostname");
    int portNumber = element->getIntAttribute("portnumber");
    return std::shared_ptr<OSCTarget> (new OSCTarget(identifier, hostName, portNumber));
}

void RelayAudioProcessor::saveMIDIRelay(std::shared_ptr<MIDIRelay> relay, XmlElement* element)
{
    element->setAttribute("identifier", relay->getIdentifier());
    element->setAttribute("group", relay->getGroup());
    element->setAttribute("channel", relay->getChannel());
    if (relay->getTarget()) element->setAttribute("target", relay->getTarget()->getIdentifier());
}

std::shared_ptr<MIDIRelay> RelayAudioProcessor::loadMIDIRelay(XmlElement* element)
{
    String identifier = element->getStringAttribute("identifier");
    String group = element->getStringAttribute("group");
    int channel = element->getIntAttribute("channel");
    std::shared_ptr<OSCTarget> target = getTargetForElement(element);
    return std::shared_ptr<MIDIRelay> (new MIDIRelay(identifier, target, group, channel));
}

void RelayAudioProcessor::saveParameterRelay(std::shared_ptr<ParameterRelay> relay, XmlElement* element)
{
    element->setAttribute("identifier", relay->getIdentifier());
    element->setAttribute("group", relay->getGroup());
    element->setAttribute("descriptor", relay->getDescriptor());
    element->setAttribute("index", relay->getIndex());
    if (relay->getTarget()) element->setAttribute("target", relay->getTarget()->getIdentifier());
}

std::shared_ptr<ParameterRelay> RelayAudioProcessor::loadParameterRelay(XmlElement* element)
{
    String identifier = element->getStringAttribute("identifier");
    String group = element->getStringAttribute("group");
    String descriptor = element->getStringAttribute("descriptor");
    int index = element->getIntAttribute("index");
    std::shared_ptr<OSCTarget> target = getTargetForElement(element);
    return std::shared_ptr<ParameterRelay> (new ParameterRelay(identifier, target, group, descriptor, index));
}

std::shared_ptr<OSCTarget> RelayAudioProcessor::getTargetForElement(XmlElement* element)
{
    std::shared_ptr<OSCTarget> target = nullptr;
    if (element->hasAttribute("target"))
    {
        try
        {
            target = oscTargetManager.getItem(element->getStringAttribute("target"));
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << "Invalid target identifier" << "\n";
        }
    }
    return target;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new RelayAudioProcessor();
}

