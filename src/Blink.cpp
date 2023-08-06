/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoHttpClient.h>
#include <NTPClient.h>
#include <SoftwareClock.h>
#include "HeatCircuit.h"
#include <ArduinoLog.h>
#include "Thermistor.h"

#define THERMISTOR_PIN_1 A0 // Replace with the analog pin connected to the B3950 thermistor for Sensor 1
#define THERMISTOR_PIN_2 A1 // Replace with the analog pin connected to the B3950 thermistor for Sensor 2

Thermistor thermistor_hk_vl(THERMISTOR_PIN_1, false, 10000, 10000, 30, 3950, 5);
Thermistor thermistor_outside(THERMISTOR_PIN_2);

#define RELAY_START_PIN 5
#define NUM_RELAYS 8

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // Replace with your desired MAC address

EthernetClient client;
EthernetUDP udp;
NTPClient timeClient(udp, "pool.ntp.org");

EthernetServer server(80); // Set the server port to 80

unsigned long lastSync = 0;
const unsigned long syncInterval = 86400000; // Sync every 24 hours (24 * 60 * 60 * 1000 milliseconds)

SoftwareClock clock;
HeatCircuit heatCircuit(THERMISTOR_PIN_1, RELAY_START_PIN, 21.0);

SingleRelay relay1(4);
SingleRelay relay2(5);
SingleRelay relay3(6);
SingleRelay relay4(7);

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


  // for (int i = 0; i < NUM_RELAYS; i++)
  // {
  //   pinMode(RELAY_START_PIN + i, OUTPUT);
  //   digitalWrite(RELAY_START_PIN + i, LOW); // Turn off all relays at startup
  // }

  // Ethernet.begin(mac);
  // server.begin();
  // udp.begin(123); // NTP uses port 123
  // timeClient.begin();

  Log.infoln("Startup complete");
}

void loop()
{
  Log.noticeln("Looping...");
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

  Serial.println("Hello World");
  delay(3000);
  relay1.turnOn();
  relay2.turnOn();
  relay3.turnOn();  
  relay4.turnOn();  


  // wait one second before repeating :)
  delay(1000);

  relay1.turnOff();
  relay2.turnOff();
  relay3.turnOff();
  relay4.turnOff();

  float temp1 = thermistor_hk_vl.readTemperature();

  Log.infoln("Temperature 1: %s", String(temp1).c_str());


  Log.noticeln("Loop complete");
}
