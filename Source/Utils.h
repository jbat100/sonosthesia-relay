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
#include <list>

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

// there are many things which follow this pattern so ended up making a template class
// template instance classes need a String getIdentifier() method, that's all

template <typename T>
class ListManager
{
public:
    
    ListManager() {}
    
    std::vector< std::shared_ptr<T> > getItems()
    {
        return items;
    }
    
    std::shared_ptr<T> newItem()
    {
        std::shared_ptr<T> item(new T);
        items.push_back(item);
        return item;
    }
    
    void deleteItem(String identifier)
    {
        for (auto i = items.begin(); i != items.end();)
        {
            if ((*i)->getIdentifier() == identifier) items.erase(i);
            else i++;
        }
    }
    
    std::shared_ptr<T> getItem(String identifier)
    {
        for (auto i = items.begin(); i != items.end();)
        {
            if ((*i)->getIdentifier() == identifier) return (*i);
        }
        
        throw std::invalid_argument( "unknown identifier" );
    }
    
    void clear()
    {
        items.clear();
    }
    
private:
    
    std::vector< std::shared_ptr<T> > items;
    
};



#endif  // UTILS_H_INCLUDED
