// PulseSensorManager.cpp
#include "PulseSensorManager.h"

PulseSensorManager::PulseSensorManager(int pulsePin, int threshold) {
  this->pulseInput = pulsePin;
  this->threshold = threshold;
  this->lastBeatTime = 0;
  this->bpm = 0;
}

void PulseSensorManager::setup() {
  pulseSensor.analogInput(pulseInput);
  pulseSensor.setThreshold(threshold);
  pulseSensor.begin();
}

void PulseSensorManager::update() {
  if (pulseSensor.sawStartOfBeat()) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastBeatTime > debounceMillis) {
      int rawBPM = pulseSensor.getBeatsPerMinute();
      lastBeatTime = currentMillis;

      // Vérifiez si la valeur brute est dans une plage plausible
      if (rawBPM >= 60 && rawBPM <= 100) {
        bpm = rawBPM; // Utilisez la valeur brute si elle est réaliste
        Serial.println("Real data");
      } else if (rawBPM > 100) { // Ajoutez cette condition pour vérifier si BPM est plus élevé que normal
        bpm = rawBPM;
        // Affichez un message d'avertissement si le BPM dépasse la valeur normale
        Serial.println("Warning: Heart rate is higher than normal.");
      } else {
        // Si la valeur est hors plage basse, simulez une valeur ou utilisez une valeur par défaut
        bpm = random(60, 101); // Remplacer par une simulation ou une logique de votre choix
        Serial.println("Simulated data");
      }
    }
  }
}

int PulseSensorManager::getBPM() {
  return bpm;
}
