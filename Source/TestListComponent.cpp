/*
  ==============================================================================

    TestListComponent.cpp
    Created: 26 May 2016 3:03:15pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TestListComponent.h"
#include "CommonComponent.h"
#include "Theme.h"

const int ParameterTestComponent::desiredHeight = 40;
const int ParameterTestComponent::hmargin = 10;


ParameterTestComponent::ParameterTestComponent(AudioProcessorParameter& _parameter) :
    slider(_parameter),
    parameter(_parameter)
{
    nameLabel.setText(parameter.getName(20), dontSendNotification);
    addAndMakeVisible(nameLabel);
    Appearence::theme()->label(nameLabel);
    
    addAndMakeVisible(slider);
}

void ParameterTestComponent::paint (Graphics& g)
{
    g.fillAll (Colours::transparentBlack);   // clear the background
    
    Rectangle<float> b = getLocalBounds().toFloat();
    
    b.setX(hmargin);
    b.setWidth( b.getWidth() - (hmargin*2) );
    b.setHeight( b.getHeight() - 10);
    
    g.setColour (Colours::grey);
    g.drawRoundedRectangle(b, 5, 1);
    g.setColour(Colours::black.withAlpha(0.5f));
    g.fillRoundedRectangle(b.reduced(1), 5);
}

void ParameterTestComponent::resized()
{
    int vmargin = 3;
    int hmargin = 10;
    int spacing = 10;
    
    int nameLabelWidth = 100;
    int labelHeight = 20;
    
    Rectangle<int> bounds = getBounds();
    
    int hackyAdjust = 20;
    Rectangle<int> rootBounds = getBounds().reduced(hmargin*2, vmargin*2).translated(hmargin - hackyAdjust, vmargin);
    
    int fullWidth = rootBounds.getWidth();
    int verticalOffset = rootBounds.getY();
    int horizontalOffset = rootBounds.getX();
    
    Rectangle<int> nameLabelBounds (horizontalOffset, verticalOffset, nameLabelWidth, labelHeight);
    horizontalOffset = nameLabelBounds.getRight() + spacing;
    nameLabel.setBounds(nameLabelBounds);
    
    int sliderWidth = fullWidth - nameLabelWidth - spacing;
    Rectangle<int> sliderBounds (horizontalOffset, verticalOffset, sliderWidth, labelHeight);
    horizontalOffset = sliderBounds.getRight() + spacing;
    slider.setBounds(sliderBounds);
}

//==============================================================================
TestListComponent::TestListComponent(RelayAudioProcessor& _processor) : processor(_processor)
{
    // Create our table component and add it to this component..
    addAndMakeVisible (listBox);
    
    listBox.setOutlineThickness(0);
    listBox.setRowHeight(ParameterTestComponent::desiredHeight + 10);
    
    listBox.setOpaque(false);
    listBox.setColour(ListBox::ColourIds::backgroundColourId, Colours::transparentBlack);
    
    listBox.setModel (this);
    
}

TestListComponent::~TestListComponent()
{
}

void TestListComponent::paint (Graphics& g)
{

}

void TestListComponent::resized()
{
    int margin = 4;
    listBox.setBounds( getBounds().withX(0).withY(10).withTrimmedBottom(10).reduced(margin) );
}

int TestListComponent::getNumRows()
{
    return processor.getParameters().size();
}

void TestListComponent::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected)
{
    
}

Component* TestListComponent::refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate)
{
    ParameterTestComponent* component = static_cast<ParameterTestComponent*> (existingComponentToUpdate);
    //ParameterSlider* component = static_cast<ParameterSlider*> (existingComponentToUpdate);
    
    // If an existing component is being passed-in for updating, we'll re-use it, but
    // if not, we'll have to create one.
    if ( component == nullptr )
    {
        AudioProcessorParameter* parameter = processor.getParameters()[rowNumber];
        if (parameter)
        {
            component = new ParameterTestComponent(*parameter);
        }
        else
        {
            std::cout << "ERROR: unexpected absent parameter for row " << rowNumber << "\n";
            return new Component(); // why does this happen?
        }
        //component = new ParameterSlider(*parameter);
    }
    
    return component;
}

