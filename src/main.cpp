#include <abstractions.hpp>
#include <Machine.h>
#include "Host.h" // Include the Host class

void setup()
{
  
  Serial.begin(115200); // Initialize default serial communication at 115200 baud

  Host host; // Create an instance of the Host class

  host.configureAppConfiguration(
      [](abstractions::configuration::IConfiguration *config) -> void
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

  host.configureServices(
      [](ServiceCollection *services) -> void
      {
        services->addService<Machine>();
      });

  host.build();
  host.run();


  logger->infoln("Starting up...");

  serviceCollection
      .addServiceWithConstructor<Machine>([](ServiceCollection *services) -> void *
                                          { return new Machine(services); });

  Machine *machine = serviceCollection.getService<Machine>();

  machine->initialize();
  machine->start();

  logger->infoln("Startup complete");

  MessageBus *messageBus = serviceCollection.getService<MessageBus>();
  messageBus->createMessageProcessingTask();
}

void loop()
{
  Logging *logger = serviceCollection.getService<Logging>();

  logger->noticeln("Looping...");

  Machine *machine = serviceCollection.getService<Machine>();

  machine->update();

  delay(100);
  logger->noticeln("Loop complete");
}