// Buzzer.h
#ifndef Buzzer_h
#define Buzzer_h

#include "Arduino.h"

class Buzzer {
  public:
    Buzzer(int pin);  // Constructor to initialize the buzzer pin
    void startBuzzer(); // Method to start the buzzer pattern
    void updateBuzzer(); // Method to handle the buzzer states
    void stopBuzzer(); // Method to stop the buzzer manually
    bool isActive(); 
  private:
    int _buzzerPin;
    unsigned long _patternStartTime;
    unsigned long _totalStartTime;
    bool _buzzerActive;
    int _state;
};

#endif
