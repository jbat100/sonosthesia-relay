/*
  ==============================================================================

    ParameterListComponent.h
    Created: 26 May 2016 3:00:19pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef PARAMETERLISTCOMPONENT_H_INCLUDED
#define PARAMETERLISTCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "OSCTargetManager.h"
#include "ParameterRelay.h"
#include "RelayComponent.h"
#include "PluginProcessor.h"
#include "ListControllerComponent.h"

class ParameterSelectionComponent : public Component, private ComboBoxListener
{
public:
    
    ParameterSelectionComponent (const OwnedArray<AudioProcessorParameter>& _parameters);
    virtual ~ParameterSelectionComponent() {}
    
    void setRelay(std::shared_ptr<ParameterRelay> _relay);
    
    void refresh();
    
    // ======== Component ==========
    
    virtual void resized() override;
    
    // ===== ComboBoxListener ======
    
    virtual void comboBoxChanged (ComboBox*) override;
    
private:
    
    int parameterIndexToId(int parameterIndex);
    int idToParameterIndex(int _id);
    
    ComboBox comboBox;
    std::shared_ptr<ParameterRelay> relay;
    const OwnedArray<AudioProcessorParameter>& parameters;
};


//==============================================================================
/*  A component associated with a target
 */

class ParameterRelayComponent : public RelayComponent {
    
public:
    
    ParameterRelayComponent(RelayAudioProcessor& _processor);
    
    virtual ~ParameterRelayComponent() {}
    
    virtual void refresh() override;
    
    virtual void setRelay (std::shared_ptr<Relay> _relay) override;
    
    // ======== Component ==========
    
    virtual void paint (Graphics&) override;
    
    virtual void resized() override;
    
    // ======== ButtonListener =========
    
    virtual void buttonClicked (Button* button) override;
    
    static const int desiredHeight;
    static const int hmargin;
    static const int vmargin;
    
private:
    
    RelayAudioProcessor& processor;
    
    Label descriptorLabel;
    Label descriptorField;
    
    Label parameterLabel;
    ParameterSelectionComponent parameterSelectionComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterRelayComponent)
    
};

//==============================================================================
/*  A component presenting a list of targets
 */

class ParameterListComponent : public Component, public ListBoxModel, public ChangeListener, public ListControllerListener
{
public:
    ParameterListComponent(RelayAudioProcessor& _processor);
    ~ParameterListComponent() {}
    
    void resized() override;
    
    // ======= ChangeListener ===========
    
    void changeListenerCallback (ChangeBroadcaster *source) override;
    
    // ======== ListBoxModel ===========
    
    int getNumRows() override;
    void paintListBoxItem (int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForRow (int rowNumber, bool isRowSelected, Component *existingComponentToUpdate) override;
    
    // ======== ListControllerListener ===========
    
    virtual void newItemRequest(Component* sender) override;
    virtual void clearItemsRequest(Component* sender) override;
    
private:
    
    ListControllerComponent listController;
    ListBox listBox;
    Font font;
    
    RelayAudioProcessor& processor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterListComponent)
};



#endif  // PARAMETERLISTCOMPONENT_H_INCLUDED
