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

bool OSCTarget::reconnect()
{
    updateSender();
    return connected;
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
    std::cout << "Connecting " << hostName << ":" << portNumber;
    if (connected) std::cout << " (success)\n";
    else std::cout << " (failure)\n";
}
