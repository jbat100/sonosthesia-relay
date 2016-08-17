/*
  ==============================================================================

    TestTableComponent.cpp
    Created: 19 May 2016 6:12:20pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "TestTableComponent.h"


/*
 ==============================================================================
 
 TestTableComponent.cpp
 Created: 12 May 2016 4:38:11pm
 Author:  Jonathan Thorpe
 
 ==============================================================================
 */

#include "../JuceLibraryCode/JuceHeader.h"

#include "CommonComponent.h"
#include "RelayComponent.h"
#include "TestTableComponent.h"

//==============================================================================
TestTableComponent::TestTableComponent(RelayAudioProcessor& _processor) : processor(_processor)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    
    // Create our table component and add it to this component..
    addAndMakeVisible (table);
    
    table.setModel (this);
    
    // give it a border
    table.setColour (ListBox::outlineColourId, Colours::grey);
    table.setOutlineThickness (1);
    
    TableHeaderComponent::ColumnPropertyFlags flags = (TableHeaderComponent::ColumnPropertyFlags)
    (TableHeaderComponent::ColumnPropertyFlags::visible |
     TableHeaderComponent::ColumnPropertyFlags::resizable);
    
    TableHeaderComponent::ColumnPropertyFlags sliderFlags = (TableHeaderComponent::ColumnPropertyFlags)
    (TableHeaderComponent::ColumnPropertyFlags::visible);
    
    table.getHeader().addColumn ("Index", indexColumnId, 60, 50, 400, flags);
    table.getHeader().addColumn ("Name", nameColumnId, 200, 50, 400, flags);
    table.getHeader().addColumn ("Value", valueColumnId, 200, 50, 400, sliderFlags);
    
    table.setRowHeight(25);
    
}

TestTableComponent::~TestTableComponent()
{
}

void TestTableComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
     draws some placeholder text to get you started.
     
     You should replace everything in this method with your own
     drawing code..
     */
    
    g.fillAll (Colours::white);   // clear the background
    
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    g.setColour (Colours::lightblue);
    g.setFont(14.0f);
    
    // draw some placeholder text
    // g.drawText ("TestTableComponent", getLocalBounds(), Justification::centred, true);
}

void TestTableComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains...
    
    int margin = 4;
    
    table.setBounds( getBounds().withX(0).withY(0).withTrimmedBottom(0).reduced(margin) );
}

void TestTableComponent::update()
{
    table.updateContent();
}


// ======= TableListBoxModel =========

int TestTableComponent::getNumRows()
{
    return processor.getParameters().size();
}

void TestTableComponent::paintRowBackground (Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected) g.fillAll (Colours::lightblue);
    else if (rowNumber % 2) g.fillAll (Colour (0xffeeeeee));
}

// This is overloaded from TableListBoxModel, and must paint any cells that aren't using custom components.
void TestTableComponent::paintCell (Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour (Colours::black);
    g.setFont (font);
    
    // we need custom components to actually be able to edit the cells which is a bit shitty but anyway...
    // so only the connected indicator can be drawn using a graphics context

    int x = 2;
    int y = 0;
    int w = width - 4;
    int h = height;
    
    AudioProcessorParameter* parameter = processor.getParameters()[rowNumber];
    
    if (columnId == indexColumnId)
    {
        g.setColour (Colours::green.withAlpha (0.5f));
        g.drawText ( String(parameter->getParameterIndex()), x, y, w, h, Justification::centredLeft, true);
    }
    
    else if (columnId == indexColumnId)
    {
        g.setColour (Colours::green.withAlpha (0.5f));
        g.drawText ( parameter->getName(20), x, y, w, h, Justification::centredLeft, true);
    }
    
}

// This is overloaded from TableListBoxModel, and must update any custom components that we're using
Component* TestTableComponent::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    
    if (columnId == valueColumnId) // For the ratings column, we return the custom combobox component
    {
        AudioProcessorParameter* parameter = processor.getParameters()[rowNumber];
        
        DemoParameterSlider* component = static_cast<DemoParameterSlider*> (existingComponentToUpdate);
        
        // If an existing component is being passed-in for updating, we'll re-use it, but
        // if not, we'll have to create one.
        if (component == nullptr) component = new DemoParameterSlider(*parameter);
        
        return component;
    }
    
    return nullptr;
    
}

int TestTableComponent::getColumnAutoSizeWidth (int columnId)
{
    return 32;
}


