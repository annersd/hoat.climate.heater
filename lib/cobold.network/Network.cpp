#include "Network.h"


// #include "ServiceCollection.h"
#include "IApplication.h"
#include "ILogger.h"

Network::Network(const char *ssid, const char *password)
    {
        this->ssid = ssid;
        this->password = password;

        // logger = cobold::app->getServices()->getService<ILogger>();
    }