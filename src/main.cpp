
#include "Cobold.hpp"
// #include "cobold_new.hpp"

#include <Machine.h>

/**
 * @brief The secret WiFi SSID and password.
 * 
 * This file is not included in the repository.
 * You need to create a file named secrets.h in the src folder with the following content:
 * 
 * #define WIFI_SSID "your ssid"
 * #define WIFI_PASSWORD "your password"
 * 
 * Replace "your ssid" and "your password" with your WiFi SSID and password.
 */
#include "secrets.h"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

cobold::hosting::IHost *host; // Declare a pointer to the Host class
cobold::Logger *logger;

void setup()
{
  Serial.begin(115200); // Initialize default serial communication at 115200 baud
  Serial.println("--- Starting setup ---");

  cobold::app->preSetup();
  cobold::app->setup();


  try
  {
    auto hostBuilder = cobold::app->getHostBuilder();
        hostBuilder->configureAppConfiguration(
        [](cobold::configuration::IConfiguration *config) -> void
        {
          // configure device
          config->setValue("device.name", "Heating Controller");

          // configure floor heating circuits
          config->setValue("heating.circuit.floor.enabled", "true");
          config->setValue("heating.circuit.floor.name", "Floor");
          config->setValue("heating.circuit.floor.thermistorPin", "34");
          config->setValue("heating.circuit.floor.valve.hotRelayPin", "5");
          config->setValue("heating.circuit.floor.valve.coldRelayPin", "6");
          config->setValue("heating.circuit.floor.pumpRelayPin", "3");
          config->setValue("heating.circuit.floor.targetTemperature", "21.0");
          config->setValue("heating.circuit.floor.maxSystemTemperature", "40.0");

          // configure heater heating circuits
          config->setValue("heating.circuit.heater.enabled", "true");
          config->setValue("heating.circuit.heater.name", "Heater");
          config->setValue("heating.circuit.heater.thermistorPin", "36");
          config->setValue("heating.circuit.heater.valve.hotRelayPin", "4");
          config->setValue("heating.circuit.heater.valve.coldRelayPin", "16");
          config->setValue("heating.circuit.heater.pumpRelayPin", "17");
          config->setValue("heating.circuit.heater.targetTemperature", "21.0");
          config->setValue("heating.circuit.heater.maxSystemTemperature", "70.0");

          // configure thermistor for outside tmeperatue
          config->setValue("heating.circuit.outside.thermistor.pin", "39");
        });

    // Configure services
    hostBuilder->configureServices(
        [](ServiceCollection *services) -> void
        {
          cobold::hosting::HostingExtensions::addHostedService<Machine>(services, [](ServiceCollection *services) -> void *
                                                                        { return new Machine(services); });

          cobold::services::ServiceCollectionExtensions<cobold::components::IComponent>::
              AddService<cobold::time::ITimeline>(services, [](ServiceCollection *services) -> void *
                                                    { return new SoftwareTimeline(0, 0); });
        });

    // Build the host
    host = hostBuilder->build();

    // Get the logger
    logger = host->getServices()->getService<cobold::Logger>();

    // Start the host
    host->start();
  }
  catch (const std::exception &e)
  {
    Serial.println("--- Unhandled Exception in startup caught ---");
    Serial.println(e.what());
  }
}

void loop()
{
  try
  {
    cobold::app->loop();
    delay(100);
  }
  catch (const std::exception &e)
  {
    Serial.println("--- Unhandled Exception in default loop caught ---");
    Serial.println(e.what());
  }
}