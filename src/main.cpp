#include <cobold.hpp>
#include <Machine.h>
#include "Host.h" // Include the Host class
#include "HostBuilder.h"

cobold::hosting::IHost *host; // Declare a pointer to the Host class
Logging *logger;

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
          config->setValue("heating.circuit.floor.hotRelayPin", "5");
          config->setValue("heating.circuit.floor.coldRelayPin", "6");
          config->setValue("heating.circuit.floor.pumpRelayPin", "3");
          config->setValue("heating.circuit.floor.targetTemperature", "21.0");

          // configure heater heating circuits
          config->setValue("heating.circuit.heater.enabled", "true");
          config->setValue("heating.circuit.heater.name", "Heater");
          config->setValue("heating.circuit.heater.thermistorPin", "1");
          config->setValue("heating.circuit.heater.hotRelayPin", "5");
          config->setValue("heating.circuit.heater.coldRelayPin", "6");
          config->setValue("heating.circuit.heater.pumpRelayPin", "4");
          config->setValue("heating.circuit.heater.targetTemperature", "21.0");

          // configure thermistor for outside tmeperatue
          config->setValue("heating.circuit.outside.thermistor.pin", "2");
        });

    hostBuilder->configureServices(
        [](ServiceCollection *services) -> void
        {
          services->addService<Machine>([](ServiceCollection *services) -> void *
                                        { return new Machine(services); });
        });

    host = hostBuilder->build();

    logger = host->getServices()->getService<Logging>();

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
    logger->noticeln("Looping...");

    Machine *machine = host->getServices()->getService<Machine>();
    machine->update();
    

    delay(1000);
    logger->noticeln("Loop complete");
  }
  catch (const std::exception &e)
  {
    Serial.println("Exception caught");
    Serial.println(e.what());
  }
}