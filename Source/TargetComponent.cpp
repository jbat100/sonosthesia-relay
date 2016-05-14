/*
  ==============================================================================

    TargetComponent.cpp
    Created: 12 May 2016 4:37:10pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "TargetComponent.h"

//==============================================================================
TargetComponent::TargetComponent(OSCTargetManager& _oscTargetManager) : font (14.0f), oscTargetManager(_oscTargetManager)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    addAndMakeVisible(newButton);
    
    newButton.addListener(this);
    newButton.setButtonText("New");
    
    // Create our table component and add it to this component..
    addAndMakeVisible (table);
    table.setModel (this);
    
    // give it a border
    table.setColour (ListBox::outlineColourId, Colours::grey);
    table.setOutlineThickness (1);
    
    table.getHeader().addColumn ("Hostname", hostnameColumnId, 200, 50, 400, TableHeaderComponent::defaultFlags);
    table.getHeader().addColumn ("Port", portColumnId, 200, 50, 400, TableHeaderComponent::defaultFlags);
    table.getHeader().addColumn ("", connectedColumnId, 200, 50, 400, TableHeaderComponent::defaultFlags);
    table.getHeader().addColumn ("", connectColumnId, 200, 50, 400, TableHeaderComponent::defaultFlags);
    
}

TargetComponent::~TargetComponent()
{
}

void TargetComponent::paint (Graphics& g)
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
    // g.drawText ("TargetComponent", getLocalBounds(), Justification::centred, true);
}

void TargetComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains...
    
    newButton.setBounds( getBounds().withX(0).withY(0).withHeight(25).reduced(4) );
}


// ======== Button::Listener =========

void TargetComponent::buttonClicked (Button* button)
{
    if (button == &newButton)
    {
        std::cout << "Make new target!\n";
        oscTargetManager.newTarget();
        this->table.repaint();
    }
}

// ======= TableListBoxModel =========

int TargetComponent::getNumRows()
{
    return oscTargetManager.getTargets().size();
}

void TargetComponent::paintRowBackground (Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected) g.fillAll (Colours::lightblue);
    else if (rowNumber % 2) g.fillAll (Colour (0xffeeeeee));
}


String TargetComponent::getText (const int columnId, const int rowNumber) const
{
    std::shared_ptr<OSCTarget> target = oscTargetManager.getTargets().at(rowNumber);
    
    if (columnId == hostnameColumnId) return target->getHostName();
    if (columnId == hostnameColumnId) return std::to_string(target->getPortNumber());
    
    return "";
}

void TargetComponent::setText (const int columnId, const int rowNumber, const String& newText)
{
    
}

// This is overloaded from TableListBoxModel, and must paint any cells that aren't using custom components.
void TargetComponent::paintCell (Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    g.setColour (Colours::black);
    g.setFont (font);
    
    std::shared_ptr<OSCTarget> target = oscTargetManager.getTargets().at(rowNumber);
    
    // we need custom components to actually be able to edit the cells which is a bit shitty but anyway...
    // so only the connected indicator can be drawn using a graphics context
    
    if (columnId == connectColumnId)
    {
        
    }
    
    /*
    if (columnId == hostnameColumnId)
        g.drawText (target->getHostName(), 2, 0, width - 4, height, Justification::centredLeft, true);
    else if (columnId == portColumnId)
        g.drawText (std::to_string(target->getPortNumber()), 2, 0, width - 4, height, Justification::centredLeft, true);
    */
    
    
     
    g.setColour (Colours::black.withAlpha (0.2f));
    g.fillRect (width - 1, 0, 1, height);
}


// This is overloaded from TableListBoxModel, and must update any custom components that we're using
Component* TargetComponent::refreshComponentForCell (int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    if (columnId == connectColumnId)
    {
        jassert (existingComponentToUpdate == nullptr);
        return nullptr;
    }
    
    if (columnId == connectColumnId) // For the ratings column, we return the custom combobox component
    {
        ButtonCustomComponent* connectComponent = static_cast<ButtonCustomComponent*> (existingComponentToUpdate);
        
        // If an existing component is being passed-in for updating, we'll re-use it, but
        // if not, we'll have to create one.
        if (connectComponent == nullptr)
            connectComponent = new ButtonCustomComponent(*this);
        
        connectComponent->setRowAndColumn (rowNumber, columnId);
        return connectComponent;
    }
    
    // The other columns are editable text columns, for which we use the custom Label component
    EditableTextCustomComponent* textLabel = static_cast<EditableTextCustomComponent*> (existingComponentToUpdate);
    
    // same as above...
    if (textLabel == nullptr)
        textLabel = new EditableTextCustomComponent (*this);
    
    textLabel->setRowAndColumn (rowNumber, columnId);
    return textLabel;
}
