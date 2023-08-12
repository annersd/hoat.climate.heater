/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>
#include <Ethernet.h>
#include <ArduinoHttpClient.h>
#include <NTPClient.h>
#include <SoftwareClock.h>
#include <ArduinoLog.h>
#include "Machine.h"

Machine machine;


byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // Replace with your desired MAC address

EthernetClient client;
EthernetUDP udp;
NTPClient timeClient(udp, "pool.ntp.org");

EthernetServer server(80); // Set the server port to 80

unsigned long lastSync = 0;
const unsigned long syncInterval = 86400000; // Sync every 24 hours (24 * 60 * 60 * 1000 milliseconds)

SoftwareClock clock;



void syncSoftwareClock()
{
  timeClient.update();
  clock.adjustOffset(timeClient.getEpochTime()); // Adjust the software clock to the current time
}

float fetchOutsideTemperature()
{
  // Implement the function to fetch the outside temperature from the NTP service or your desired API.
  // This function should return the current outside temperature in Celsius.
  // Replace the return statement with your implementation.
  return 10.0; // Example value for outside temperature
}
String readRequest(EthernetClient &client)
{
  String request = "";

  while (client.connected())
  {
    if (client.available())
    {
      char c = client.read();
      request += c;
      if (request.endsWith("\r\n\r\n"))
      {
        break;
      }
    }
  }

  return request;
}

void setup()
{
  Serial.begin(9600);

  // Initialize with log level and log output.
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);

  Log.infoln("Starting up...");

machine.initialize();
machine.start();

  Log.infoln("Startup complete");
}

void loop()
{
  Log.noticeln("Looping...");
  machine.update();
  // clock.reset(); // Reset the software clock at the beginning of the loop

  // EthernetClient client = server.available();

  // if (client)
  // {
  //   String request = readRequest(client);
  //   handleRequest(request, client);
  //   client.stop();
  // }

  // if (millis() - lastSync >= syncInterval)
  // {
  //   syncSoftwareClock();
  //   lastSync = millis();
  // }

  // float outsideTemp = fetchOutsideTemperature();
  // heatCircuit.update(outsideTemp);

  delay(100);
  Log.noticeln("Loop complete");
}
