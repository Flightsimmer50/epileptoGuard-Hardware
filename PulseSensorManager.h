// PulseSensorManager.h
#ifndef PulseSensorManager_h
#define PulseSensorManager_h

#include <Arduino.h>
#include <PulseSensorPlayground.h>

class PulseSensorManager {
public:
  PulseSensorManager(int pulsePin, int threshold);
  void setup();
  void update();
  int getBPM();

private:
  int pulseInput;
  int threshold;
  PulseSensorPlayground pulseSensor;
  unsigned long lastBeatTime;
  const unsigned long debounceMillis = 250; // Adjust as necessary
  int bpm;
};

#endif
