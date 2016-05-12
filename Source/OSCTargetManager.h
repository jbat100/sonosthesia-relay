/*
  ==============================================================================

    OSCTargetManager.h
    Created: 12 May 2016 4:47:23pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#ifndef OSCTARGETMANAGER_H_INCLUDED
#define OSCTARGETMANAGER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include <list>
#include <memory>


class OSCTarget
{
public:
    
    OSCTarget();
    OSCTarget(String _hostName, int _portNumber);
    
    void setHostName(String _hostName);
    String getHostName();
    
    void setPortNumber(int _portNumber);
    int getPortNumber();
    
    String getIdentifier();
    
    OSCSender& getSender();
    
private:
    
    String hostName;
    int portNumber;
    String identifier;
    OSCSender sender;
    
    void updateSender();
};


class OSCTargetManager
{
public:
    
    std::list< std::shared_ptr<OSCTarget> > getTargets();
    
    std::shared_ptr<OSCTarget> newTarget();
    
    void deleteTarget(String identifier);
    
private:
    std::list< std::shared_ptr<OSCTarget> > targets;
};


#endif  // OSCTARGETMANAGER_H_INCLUDED
