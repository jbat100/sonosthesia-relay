/*
  ==============================================================================

    ParameterRelayManager.cpp
    Created: 12 May 2016 4:49:08pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "ParameterRelay.h"

const int ParameterRelay::noIndex = -1;
const float ParameterRelay::noValue = std::numeric_limits<float>::min();
const float ParameterRelay::threshold = 1e-6;

ParameterRelay::ParameterRelay() : Relay(), index(-1)
{    
}

ParameterRelay::ParameterRelay(std::shared_ptr<OSCTarget> _target, String _group, String _descriptor, int _index) :
Relay(_target, _group),
descriptor(_descriptor),
index(_index),
lastValue(noValue)
{
}

void ParameterRelay::setIndex(int _index)
{
    index = _index;
    lastValue = noValue;
}

int ParameterRelay::getIndex()
{
    return index;
}

void ParameterRelay::setDescriptor(String _descriptor)
{
    descriptor = _descriptor;
    resend();
}

String ParameterRelay::getDescriptor()
{
    return descriptor;
}


void ParameterRelay::relay(int _index, float value)
{
    if (_index == index && std::abs(value - lastValue) > threshold)
    {
        send(value);
    }
}

void ParameterRelay::resend()
{
    if (lastValue != noValue) send(lastValue);
}

void ParameterRelay::setTarget(std::shared_ptr<OSCTarget> _target)
{
    Relay::setTarget(_target);
    resend();
}

void ParameterRelay::setGroup(String _group)
{
    Relay::setGroup(_group);
    resend();
}

void ParameterRelay::send(float value)
{
    lastValue = value;
    
    auto target = getTarget();
    if (target)
    {
        OSCAddressPattern pattern = OSCAddressPattern("/" + getGroup() + "/" + getDescriptor() + "/");
        OSCMessage message = OSCMessage(pattern, value);
        target->sendMessage(message);
    }
}

ParameterRelayManager::ParameterRelayManager(AudioProcessor& _processor) : processor(_processor)
{
    
}

void ParameterRelayManager::refresh()
{
    const OwnedArray< AudioProcessorParameter > & parameters = processor.getParameters();
    
    auto relays = getItems();
    
    for (auto i = parameters.begin(); i != parameters.end(); i++)
    {
        int index = (*i)->getParameterIndex();
        float value = (*i)->getValue();
        
        for (auto r = relays.begin(); r != relays.end(); r++)
        {
            (*r)->relay(index, value);
        }
    }
    
}

