/*
  ==============================================================================

    ParameterRelayManager.cpp
    Created: 12 May 2016 4:49:08pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "ParameterRelay.h"

ParameterRelay::ParameterRelay() : Relay(nullptr), index(-1), address("")
{    
}

ParameterRelay::ParameterRelay(int _index, std::shared_ptr<OSCTarget> _target, OSCAddress _address) :
Relay(_target),
index(_index),
address(_address)
{
}

void ParameterRelay::setIndex(int _index)
{
    index = _index;
}

int ParameterRelay::getIndex()
{
    return index;
}

void ParameterRelay::setAddress(OSCAddress _address)
{
    address = _address;
}

OSCAddress ParameterRelay::getAddress()
{
    return address;
}


void ParameterRelay::relay(int index, float value)
{
    
}
