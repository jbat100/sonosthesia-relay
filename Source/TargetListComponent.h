/*
  ==============================================================================

    TargetListComponent.h
    Created: 26 May 2016 3:00:51pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef TARGETLISTCOMPONENT_H_INCLUDED
#define TARGETLISTCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "OSCTargetManager.h"

//==============================================================================
/*  A component associated with a target
 */

class TargetComponent : public Component, public LabelListener, public ButtonListener, public OSCTargetListener  {
    
    TargetComponent(OSCTargetManager& _manager, std::shared_ptr<OSCTarget> _target);
    
    void paint (Graphics&) override;
    void resized() override;
    
    // ======== ButtonListener =========
    
    void refresh();
    
    // ======== ButtonListener =========
    
    void buttonClicked (Button* button) override;
    
    // ======== LabelListener ==========
    
    void labelTextChanged(Label *label) override;
    
    // ====== OSCTargetListener ========
    
    void targetInvalidated(OSCTarget* _target) override;
    
private:
    
    OSCTargetManager& manager;
    std::shared_ptr<OSCTarget> target;
    
    Label hostLabel;
    Label hostField;
    
    Label portLabel;
    Label portField;
    
    Label statusLabel;
    
    TextButton deleteButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TargetComponent)
    
};


//==============================================================================
/*  A component presenting a list of targets
*/

class TargetListComponent : public Component, public ButtonListener, public ListBoxModel
{
public:
    TargetListComponent(OSCTargetManager& oscTargetManager);
    ~TargetListComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    // ======== ButtonListener =========
    
    void buttonClicked (Button* button) override;
    
    // ======== ListBoxModel ===========
    
    int getNumRows() override;
    void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) override;

private:
    
    TextButton newButton;
    TextButton clearButton;
    ListBox table;
    Font font;
    
    OSCTargetManager& oscTargetManager;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TargetListComponent)
};


#endif  // TARGETLISTCOMPONENT_H_INCLUDED
