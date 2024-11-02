// Buzzer.cpp
#include "Buzzer.h"

Buzzer::Buzzer(int pin) {
  _buzzerPin = pin;
  pinMode(_buzzerPin, OUTPUT);
  _buzzerActive = false;
  _state = 0;
}

void Buzzer::startBuzzer() {
  _buzzerActive = true;  // Enable the continuous buzzer activity
}

void Buzzer::updateBuzzer() {
  if (!_buzzerActive) {
    digitalWrite(_buzzerPin, LOW);
    return;
  }

  // Ici, nous créons un motif de buzzer qui continue indéfiniment
  unsigned long currentMillis = millis();
  switch (_state) {
    case 0:
    case 2:
      digitalWrite(_buzzerPin, HIGH); // Buzzer ON
      if (currentMillis - _patternStartTime >= 100) {
        digitalWrite(_buzzerPin, LOW); // Buzzer OFF
        _patternStartTime = currentMillis;
        _state++;
      }
      break;
    case 1:
    case 3:
      if (currentMillis - _patternStartTime >= 200) {
        _patternStartTime = currentMillis;
        _state = (_state + 1) % 4; // Cycle through states 0-3
      }
      break;
  }
}
bool Buzzer::isActive() {
  return _buzzerActive;
}

void Buzzer::stopBuzzer() {
  _buzzerActive = false;  // Disable the buzzer activity
  digitalWrite(_buzzerPin, LOW);  // Immediately stop the buzzer
  _state = 0;  // Reset the state
}
