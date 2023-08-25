#include <cobold.hpp>
#include <Machine.h>
#include "Host.h" // Include the Host class
#include "HostBuilder.h"
#include "HostingExtensions.h"

cobold::hosting::IHost *host; // Declare a pointer to the Host class
ILogger *logger;

void setup()
{
  Serial.begin(115200); // Initialize default serial communication at 115200 baud
  Serial.println("Starting setup...");

  try
  {

    cobold::hosting::IHostBuilder *hostBuilder = new cobold::hosting::HostBuilder(); // Create an instance of the Host class

    hostBuilder->configureAppConfiguration(
        [](cobold::configuration::IConfiguration *config) -> void
        {
          // configure device
          config->setValue("device.name", "Heating Controller");

          // configure floor heating circuits
          config->setValue("heating.circuit.floor.enabled", "true");
          config->setValue("heating.circuit.floor.name", "Floor");
          config->setValue("heating.circuit.floor.thermistorPin", "0");
          config->setValue("heating.circuit.floor.valve.hotRelayPin", "5");
          config->setValue("heating.circuit.floor.valve.coldRelayPin", "6");
          config->setValue("heating.circuit.floor.pumpRelayPin", "3");
          config->setValue("heating.circuit.floor.targetTemperature", "21.0");

          // configure heater heating circuits
          config->setValue("heating.circuit.heater.enabled", "true");
          config->setValue("heating.circuit.heater.name", "Heater");
          config->setValue("heating.circuit.heater.thermistorPin", "1");
          config->setValue("heating.circuit.heater.valve.hotRelayPin", "5");
          config->setValue("heating.circuit.heater.valve.coldRelayPin", "6");
          config->setValue("heating.circuit.heater.pumpRelayPin", "4");
          config->setValue("heating.circuit.heater.targetTemperature", "21.0");

          // configure thermistor for outside tmeperatue
          config->setValue("heating.circuit.outside.thermistor.pin", "2");
        });

    hostBuilder->configureServices(
        [](ServiceCollection *services) -> void
        {
          cobold::hosting::HostingExtensions::addHostedService<Machine>(services, [](ServiceCollection *services) -> void *
                                                                        { return new Machine(services); });
        });

    host = hostBuilder->build();

    logger = host->getServices()->getService<ILogger>();

    host->start();
  }
  catch (const std::exception &e)
  {
    Serial.println("Exception caught");
    Serial.println(e.what());
  }
}

void loop()
{
  try
  {
    logger->info("Looping...");

    Machine *machine = host->getServices()->getService<Machine>();
    machine->update();
    

    delay(1000);
    logger->info("Loop complete");
  }
  catch (const std::exception &e)
  {
    Serial.println("Exception caught");
    Serial.println(e.what());
  }
}