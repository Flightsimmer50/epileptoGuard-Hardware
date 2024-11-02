#ifndef BLETOOTH_H
#define BLETOOTH_H
#include <Arduino.h>

#include "constants.h"
#include "BluetoothSerial.h"  // Nombre de caractères envoyés max est de 455 et prend environt 7 secondes à arriver dans flutter

void setupBluetooth(BluetoothSerial& SerialBT);
void handleBluetooth(BluetoothSerial& SerialBT);

#endif