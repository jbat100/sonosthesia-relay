/*
  ==============================================================================

    CommonComponent.h
    Created: 15 May 2016 12:54:24am
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef COMMONCOMPONENT_H_INCLUDED
#define COMMONCOMPONENT_H_INCLUDED


#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
// This is a handy slider subclass that controls an AudioProcessorParameter
// Taken from the juce audio plugin demo

class ParameterSlider   : public Slider, private Timer
{
public:
    ParameterSlider (AudioProcessorParameter& p) : Slider (p.getName (256)), param (p)
    {
        setRange (0.0, 1.0, 0.0);
        startTimerHz (30);
        updateSliderPos();
    }
    
    void valueChanged() override
    {
        std::cout << "ParameterSlider changed " << param.getName(20) << " to " << Slider::getValue() << "\n";
        param.setValueNotifyingHost ((float) Slider::getValue());
    }
    
    void timerCallback() override       { updateSliderPos(); }
    
    void startedDragging() override     { param.beginChangeGesture(); }
    void stoppedDragging() override     { param.endChangeGesture();   }
    
    double getValueFromText (const String& text) override   { return param.getValueForText (text); }
    String getTextFromValue (double value) override         { return param.getText ((float) value, 1024); }
    
    void updateSliderPos()
    {
        const float newValue = param.getValue();
        
        if (newValue != (float) Slider::getValue() && ! isMouseButtonDown())
            Slider::setValue (newValue);
    }
    
    AudioProcessorParameter& param;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterSlider)
};

//==============================================================================
// This is a custom Label manager and component, which we use for the table's editable text columns.

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



//==============================================================================
// This is a custom Slider manager and component, which we use for the table'slider columns.


class SliderCellManager {
    
public:
    
    virtual ~SliderCellManager() {}
    virtual void cellSliderValueChanged(const int rowNumber, const int columnId, const double value) = 0;
    virtual double getSliderCellValue(const int rowNumber, const int columnId) = 0;
    
};

class SliderCellComponent  : public Component, public Slider::Listener
{
public:
    SliderCellComponent (SliderCellManager& _manager)  : manager (_manager)
    {
        //setColour (textColourId, Colours::black);
        
        slider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
        slider.setRange(0.0, 1.0);
        
        addAndMakeVisible(slider);
    }
    
    virtual void resized() override
    {
        slider.setBounds(getBounds().reduced(2));
    }
    
    virtual void sliderValueChanged(Slider *_slider) override
    {
        if (_slider != &slider) throw std::runtime_error("unexpected slider");
        manager.cellSliderValueChanged(columnId, row, slider.getValue() );
    }
    
    void setRowAndColumn (const int newRow, const int newColumn)
    {
        row = newRow;
        columnId = newColumn;
        slider.setValue( manager.getSliderCellValue(columnId, row), dontSendNotification );
    }
    
private:
    Slider slider;
    SliderCellManager& manager;
    int row, columnId;
};



//==============================================================================
// This is a custom component containing used for selecting an audio parameter




#endif  // COMMONCOMPONENT_H_INCLUDED
