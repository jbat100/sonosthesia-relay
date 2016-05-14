/*
  ==============================================================================

    OSCTargetManager.cpp
    Created: 12 May 2016 4:47:23pm
    Author:  Jonathan Thorpe

  ==============================================================================
*/

#include "OSCTargetManager.h"

OSCTarget::OSCTarget() :
    hostName("127.0.0.1"),
    portNumber(3333),
    connected(false),
    identifier(Uuid().toString())
{
    updateSender();
}

OSCTarget::OSCTarget(String _hostName, int _portNumber) :
    hostName(_hostName),
    portNumber(_portNumber),
    connected(false),
    identifier(Uuid().toString())
{
    updateSender();
}

bool OSCTarget::isConnected()
{
    return connected;
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
    connected = sender.connect(hostName, portNumber);
}

const std::vector< std::shared_ptr<OSCTarget> > OSCTargetManager::getTargets() const
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
    for (auto i = targets.begin(); i != targets.end();)
    {
        if ((*i)->getIdentifier() == identifier) targets.erase(i);
        else i++;
    }
}

void OSCTargetManager::clear()
{
    targets.clear();
}
