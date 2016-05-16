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

#include <vector>
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
    
    bool reconnect();
    
    bool isConnected();
    
    String getIdentifier();
    
    OSCSender& getSender();
    
private:
    
    String hostName;
    int portNumber;
    OSCSender sender;
    bool connected;
    
    String identifier;
    
    void updateSender();
};


class OSCTargetManager
{
public:
    
    const std::vector< std::shared_ptr<OSCTarget> > getTargets() const;
    
    std::shared_ptr<OSCTarget> newTarget();
    
    void deleteTarget(String identifier);
    
    void clear();
    
private:
    std::vector< std::shared_ptr<OSCTarget> > targets;
};


#endif  // OSCTARGETMANAGER_H_INCLUDED
