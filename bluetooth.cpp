#include "bluetooth.h"

void checkBTAndSerialAvailable(){
  // Check if Bluetooth is available
  #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
    #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
  #endif

  // Check Serial Port Profile
  #if !defined(CONFIG_BT_SPP_ENABLED)
    #error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
  #endif

}

void setupBluetooth(BluetoothSerial& SerialBT) {
  checkBTAndSerialAvailable();
  SerialBT.begin(Constants::deviceName); //Bluetooth device name
  // SerialBT.deleteAllBondedDevices(); // Uncomment this to delete paired devices; Must be called after begin
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it to the phone with Bluetooth!\n", Constants::deviceName);
}

void handleBluetooth(BluetoothSerial& SerialBT) {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
}