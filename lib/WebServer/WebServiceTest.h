#include <Ethernet.h>


void handleTemperatureRequest(EthernetClient &client)
{
//   float temp1 = thermistor_hk_vl.readTemperature();
//   float temp2 = thermistor_outside.readTemperature();

//   String response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
//   response += "Temperature 1: " + String(temp1) + "°C\r\n";
//   response += "Temperature 2: " + String(temp2) + "°C\r\n";

//   response += "Outside Temperature: " + String(fetchOutsideTemperature()) + "°C\r\n";

//   client.print(response);
}

void handleNotFound(EthernetClient &client)
{
  String response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n";
  response += "Page not found\r\n";

  client.print(response);
}

void handleRequest(const String &request, EthernetClient &client)
{
  if (request.indexOf("GET /temperature") != -1)
  {
    handleTemperatureRequest(client);
  }
  else
  {
    handleNotFound(client);
  }
}
