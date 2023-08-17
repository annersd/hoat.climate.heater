
#include <Machine.h>
#include "config/config.h"

Machine machine;

void setup()
{
  // configureMachine(machine);

  Serial.begin(115200);

  // Initialize with log level and log output.
  Log.begin(DEFAULT_LOG_LEVEL, &Serial);

  Log.infoln("Starting up...");

  machine.initialize();
  machine.start();

  Log.infoln("Startup complete");

  
}

void loop()
{
  Log.noticeln("Looping...");
  machine.update();
 
  delay(100);
  Log.noticeln("Loop complete");
}

void configureMachine(Machine& machine)
{
  machine.Config->setValue("device.name", "Heating Controller");

  machine.Config->setValue("heating.circuit.floor.enabled", "true");
  machine.Config->setValue("heating.circuit.floor.name", "Floor");
  machine.Config->setValue("heating.circuit.floor.thermistorPin", "0");
  machine.Config->setValue("heating.circuit.floor.hotRelayPin", "5");
  machine.Config->setValue("heating.circuit.floor.coldRelayPin", "6");
  machine.Config->setValue("heating.circuit.floor.pumpRelayPin", "3");
  machine.Config->setValue("heating.circuit.floor.targetTemperature", "21.0");

  machine.Config->setValue("heating.circuit.heater.enabled", "true");
  machine.Config->setValue("heating.circuit.heater.name", "Heater");
  machine.Config->setValue("heating.circuit.heater.thermistorPin", "1");
  machine.Config->setValue("heating.circuit.heater.hotRelayPin", "5");
  machine.Config->setValue("heating.circuit.heater.coldRelayPin", "6");
  machine.Config->setValue("heating.circuit.heater.pumpRelayPin", "4");
  machine.Config->setValue("heating.circuit.heater.targetTemperature", "21.0");

  // configure thermistor for outside tmeperatue
  machine.Config->setValue("heating.circuit.outside.thermistor.pin", "2");



}