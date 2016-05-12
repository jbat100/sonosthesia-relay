/*
  ==============================================================================

    OSCTargetManager.cpp
    Created: 12 May 2016 4:47:23pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "OSCTargetManager.h"

OSCTarget::OSCTarget()
{
    hostName = String("127.0.0.1");
    portNumber = 3333;
    identifier = Uuid().toString();
    updateSender();
}

OSCTarget::OSCTarget(String _hostName, int _portNumber) : hostName(_hostName), portNumber(_portNumber)
{
    identifier = Uuid().toString();
    updateSender();
}
    
void OSCTarget::setHostName(String _hostName)
{
    hostName = _hostName;
    updateSender();
}

String OSCTarget::getHostName()
{
    return hostName;
}
    
void OSCTarget::setPortNumber(int _portNumber)
{
    portNumber = _portNumber;
    updateSender();
}

int OSCTarget::getPortNumber()
{
    return portNumber;
}
    
String OSCTarget::getIdentifier()
{
    return identifier;
}

void OSCTarget::updateSender()
{
    sender.disconnect();
    sender.connect(hostName, portNumber);
}

std::list< std::shared_ptr<OSCTarget> > OSCTargetManager::getTargets()
{
    return targets;
}

std::shared_ptr<OSCTarget> OSCTargetManager::newTarget()
{
    std::shared_ptr<OSCTarget> target ( new OSCTarget() );
    targets.push_back(target);
    return target;
}

void OSCTargetManager::deleteTarget(String identifier)
{
    for (auto i = targets.begin(); i != targets.end(); ++i)
    {
        if ((*i)->getIdentifier() == identifier) targets.erase(i--);
    }
}
