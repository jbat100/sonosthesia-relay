/*
  ==============================================================================

    Theme.cpp
    Created: 28 May 2016 6:40:22pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "Theme.h"


std::shared_ptr<Theme> Appearence::themeInstance = std::shared_ptr<Theme> (new SpaceTheme());

std::shared_ptr<Theme> Appearence::theme()
{
    return themeInstance;
}

void Appearence::setTheme(Name name)
{
    switch (name) {
            
        case Space:
            themeInstance = std::shared_ptr<Theme>( new SpaceTheme() );
            break;
            
        default:
            themeInstance = std::shared_ptr<Theme>( new SpaceTheme() );
            throw std::invalid_argument("unimplemented theme");
            break;
    }
}

void SpaceTheme::label(Label& label, Level level)
{
    label.setColour(Label::ColourIds::textColourId, Colours::whitesmoke);
}

void SpaceTheme::field(Label& label, Level level)
{
    label.setColour( Label::ColourIds::textColourId, Colours::darkgrey);
    label.setColour( Label::ColourIds::backgroundColourId, Colours::whitesmoke);
    label.setColour( Label::ColourIds::backgroundWhenEditingColourId, Colours::lightblue);
}

void SpaceTheme::textButton(TextButton& textButton, Level level)
{
    
}

void SpaceTheme::paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected, Level level)
{
    
}

