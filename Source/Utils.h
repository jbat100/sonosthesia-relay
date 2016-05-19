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
class ListManager : public ChangeBroadcaster
{
public:
    
    ListManager() {}
    
    // avoid using this, better to use number of items and getter
    std::vector< std::shared_ptr<T> > getItems()
    {
        return items;
    }
    
    int count() {
        return items.size();
    }
    
    std::shared_ptr<T> newItem()
    {
        std::shared_ptr<T> item(new T);
        items.push_back(item);
        sendChangeMessage();
        return item;
    }
    
    void deleteItem(String identifier)
    {
        for (auto i = items.begin(); i != items.end();)
        {
            if ((*i)->getIdentifier() == identifier) items.erase(i);
            else i++;
        }
        sendChangeMessage();
    }
    
    std::shared_ptr<T> getItem(String identifier)
    {
        //std::cout << "ListManager getItem " << identifier << "\n";
        
        for (auto i = items.begin(); i != items.end(); i++)
        {
            if ((*i)->getIdentifier() == identifier) return (*i);
        }
        
        throw std::invalid_argument( "unknown identifier" );
    }
    
    std::shared_ptr<T> getItem(int index)
    {
        return items.at(index);
    }
    
    void clear()
    {
        items.clear();
        sendChangeMessage();
    }
    
private:
    
    std::vector< std::shared_ptr<T> > items;
    
};

//==============================================================================
// This is a custom Label component, which we use for the table's editable text columns.

class TextCellManager {
    
public:
    
    virtual ~TextCellManager() {}
    virtual void cellTextChanged(const int newRow, const int newColumn, const String& newText) = 0;
    virtual String getCellText(const int newRow, const int newColumn) = 0;
    
};

class TextCellComponent  : public Label
{
public:
    TextCellComponent (TextCellManager& _manager)  : manager (_manager)
    {
        // double click to edit the label text; single click handled below
        setEditable (false, true, false);
        setColour (textColourId, Colours::black);
    }
    
    void textWasEdited() override
    {
        manager.cellTextChanged(columnId, row, getText());
    }
    
    void setRowAndColumn (const int newRow, const int newColumn)
    {
        row = newRow;
        columnId = newColumn;
        setText (manager.getCellText(columnId, row), dontSendNotification);
    }
    
private:
    TextCellManager& manager;
    int row, columnId;
};



#endif  // UTILS_H_INCLUDED
