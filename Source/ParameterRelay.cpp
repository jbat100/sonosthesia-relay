/*
  ==============================================================================

    ParameterRelayManager.cpp
    Created: 12 May 2016 4:49:08pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "ParameterRelay.h"

ParameterRelay::ParameterRelay() : Relay(), index(-1)
{    
}

ParameterRelay::ParameterRelay(std::shared_ptr<OSCTarget> _target, String _group, String _descriptor, int _index) :
Relay(_target, _group),
descriptor(_descriptor),
index(_index)
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

void ParameterRelay::setDescriptor(String _descriptor)
{
    descriptor = _descriptor;
}

String ParameterRelay::getDescriptor()
{
    return descriptor;
}


void ParameterRelay::relay(int index, float value)
{
    
}
