/*
  ==============================================================================

    TestComponent.h
    Created: 19 May 2016 6:12:20pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef TESTCOMPONENT_H_INCLUDED
#define TESTCOMPONENT_H_INCLUDED


#include "../JuceLibraryCode/JuceHeader.h"

#include "CommonComponent.h"
#include "PluginProcessor.h"

//==============================================================================
/*
 */
class TestComponent : public Component, public TableListBoxModel
{
public:
    TestComponent(RelayAudioProcessor& _processor);
    ~TestComponent();
    
    void paint (Graphics&) override;
    void resized() override;
    
    void update();
    
    // ======= TableListBoxModel =========
    
    int getNumRows() override;
    void paintRowBackground (Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
    void paintCell (Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    int getColumnAutoSizeWidth (int columnId) override;
    
private:
    
    TableListBox table;
    Font font;
    
    const int indexColumnId = 1;
    const int nameColumnId = 2;
    const int valueColumnId = 3;
    
    RelayAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestComponent)
};



#endif  // TESTCOMPONENT_H_INCLUDED
