/*
  ==============================================================================

    Theme.h
    Created: 28 May 2016 6:40:22pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef THEME_H_INCLUDED
#define THEME_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class Theme;

class Appearence
{
public:
    
    enum Name {
        Space,
        Dusk
    };
    
    static std::shared_ptr<Theme> theme();
    
    static void setTheme(Name name);
    
private:
    
    static std::shared_ptr<Theme> themeInstance;
    
};

class Theme
{
    
public:
    
    enum Level {
        Default,
        Info,
        Primary,
        Warning,
        Error
    };
    
    virtual ~Theme() {}
    
    virtual void label(Label& label, Level level = Default) = 0;
    virtual void field(Label& label, Level level = Default) = 0;
    
    // TODO : have an indicator mode for labels for example for connected/disconnected
    
    virtual void textButton(TextButton& textButton, Level level = Default) = 0;
    
    virtual void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected, Level level = Default) = 0;
    
};

class SpaceTheme : public Theme {
    
    void label(Label& label, Level level = Default) override;
    void field(Label& label, Level level = Default) override;
    
    
    
    void textButton(TextButton& textButton, Level level = Default) override;
    
    void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected, Level level = Default) override;
    
};


#endif  // THEME_H_INCLUDED
