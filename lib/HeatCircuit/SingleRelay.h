#ifndef SINGLE_RELAY_H
#define SINGLE_RELAY_H

#include <Arduino.h>
#include <ArduinoLog.h>

class SingleRelay {
private:
  int pin;
  bool isOn;
  bool isNormallyOpen;

public:
  SingleRelay(){};
  SingleRelay(int relayPin, bool normallyOpen = true)
    : pin(relayPin), isOn(false), isNormallyOpen(normallyOpen) {
    pinMode(pin, OUTPUT);
    turnOff();
  }

  void turnOn() {
    Log.infoln("Turning on relay on pin %d", pin);
    digitalWrite(pin, isNormallyOpen ? HIGH : LOW);
    isOn = true;
  }

  void turnOff() {
    Log.infoln("Turning off relay on pin %d", pin);
    digitalWrite(pin, isNormallyOpen ? LOW : HIGH);
    isOn = false;
  }

  bool getState() const {
    return isOn;
  }

  bool isNO() const {
    return isNormallyOpen;
  }

  bool isNC() const {
    return !isNormallyOpen;
  }
};


#endif // !SINGLE_RELAY_H