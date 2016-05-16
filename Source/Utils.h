/*
  ==============================================================================

    Utils.h
    Created: 16 May 2016 5:01:21pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <map>

#include "../JuceLibraryCode/JuceHeader.h"

// we generate identifiers using the juce uuid class (which generates Strings) but many user interface components want int ids
// this class gives an easy way to associate ints with Strings. Note the ints will not be globally unique but unique to this
// generator, possible issue: running out of ints

class NumericIdentifierGenerator
{
public:
    NumericIdentifierGenerator();
    
    // generates incremental int ids
    int getNumericIdentifier(String identifier);
    
    // throws if int is not known by the generator
    String getStringIdentifier(int identifier);
    
private:
    std::map<String, int> identifiers;
    int counter;
};



#endif  // UTILS_H_INCLUDED
