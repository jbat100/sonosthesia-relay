/*
  ==============================================================================

    Utils.cpp
    Created: 16 May 2016 5:01:21pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include <stdexcept>

#include "Utils.h"

NumericIdentifierGenerator::NumericIdentifierGenerator() : counter(0) {}

int NumericIdentifierGenerator::getNumericIdentifier(String identifier)
{
    auto i = identifiers.find(identifier);
    
    if (i == identifiers.end())
    {
        identifiers[identifier] = counter;
        counter++;
        return identifiers[identifier];
    }
    
    return i->second;
}

String NumericIdentifierGenerator::getStringIdentifier(int identifier)
{
    for (auto i = identifiers.begin(); i != identifiers.end(); i++)
    {
        if (i->second == identifier) return i->first;
    }
    
    throw std::invalid_argument( "unknown identifier" );
}
