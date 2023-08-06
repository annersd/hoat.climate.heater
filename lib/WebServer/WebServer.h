
#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <Arduino.h>
#include <Ethernet.h>

class WebServer
{
private:
    /* data */
    Client &client;

public:
    WebServer(Client &client);
    ~WebServer();
};

WebServer::WebServer( Client &client )
{
    this->client = client;
}

WebServer::~WebServer()
{
}


#endif // !WEBSERVER_H