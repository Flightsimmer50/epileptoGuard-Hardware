// Put your libraries here, to import them:
#include "bluetooth.h"

// Put your external files here, to includes functions:
#include "constants.h"
#include "bluetooth.h"
#include "myo.h"
#include "PulseSensorManager.h"
#include "Buzzer.h"
#include "DFPlayerCommands.h"


// Put your global code here, to declare variables and other:
BluetoothSerial SerialBT;
PulseSensorManager pulseSensorManager(34,Constants::PULSE_THRESHOLD);

//String de récupération des données -> 10 min / 10 sec interval = 60 valeurs
String bpmStr= "bpm";
String emgStr= "emg";
String imuStr= "imu";
int lastIndex = 0;
long initialTime = millis();
Buzzer buzzer(15);
const int buttonPin = 16;

bool SeizureMonitoringOn = true;

void dataProcessing() {
  //get sensor data for this instant

  int bpm =  pulseSensorManager.getBPM();

  int imu = getImuData(); // axe w
  int emg = getEmgData(); //  8 en un


  //activer et desactiver la detection de crise
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    String receivedString = SerialBT.readString();
    Serial.write((const uint8_t*)receivedString.c_str(), receivedString.length());
    if (receivedString.equals("true")) {
        SeizureMonitoringOn = true;
    } else if (receivedString.equals("false")) {
        SeizureMonitoringOn = false;
    }
    Serial.println(SeizureMonitoringOn ? "true" : "false");
  }


  //ici ajouter la detection de crise en temps reel (avec variable Monitoring actif)
  if(bpm > 100 && emg > 35 && SeizureMonitoringOn){
    //déclencher le buzzer pendant 20 second 
    buzzer.startBuzzer(); // dont wanna work when i add bpm
   
   Serial.println("bpm : "+bpm);

    //envoie de l'alerte crise par BLE avec le mot clef cri
    SerialBT.write((const uint8_t *)"cri", 3); // "cri" is 3 characters long
     Serial.println("CRISE");
  }

  // Vérifier l'intervalle de 10 secondes
  long currentTime =  millis();
  if (currentTime - initialTime >= 1000) { // 10 secondes en millisecondes
    // Réinitialiser le temps initial
    initialTime = currentTime;
    if (lastIndex < 10) { // Vérifier si le tableau n'est pas plein
      bpmStr = bpmStr + "," + bpm;
      emgStr = emgStr + "," + emg;
      imuStr = imuStr + "," + imu;
      lastIndex++; // Mettre à jour l'index du dernier élément utilisé
    }
  }

  // ici, toutes les 10 minutes (index = 60),envoyer et vider les tableaux
  if (lastIndex == 10) {
    bpmStr = bpmStr + "\n";
    emgStr = emgStr + "\n";
    imuStr = imuStr + "\n";
    //envoyer les données par BLE
    SerialBT.write((const uint8_t*)bpmStr.c_str(), bpmStr.length());
    SerialBT.write((const uint8_t*)emgStr.c_str(), emgStr.length());
    SerialBT.write((const uint8_t *)imuStr.c_str(), imuStr.length());

    // Réinitialiser le temps initial et l'index du dernier élément utilisé
    initialTime = currentTime;
    lastIndex = 0;
    // Effacer le contenu des Strings en réinitialisant toutes les valeurs à une valeur par défaut
    bpmStr= "bpm";
    emgStr= "emg";
    imuStr= "imu";
  }
}

void setup() {
  Serial.begin(115200);
  setupBluetooth(SerialBT);
  pulseSensorManager.setup();
  pinMode(buttonPin, INPUT_PULLUP);
  delay(1000); // Allow time for the sensor to stabilize
}

void loop() {
  handleBluetooth(SerialBT);
  myo_connect();
  pulseSensorManager.update();
  dataProcessing();
  
  static bool buttonWasReleased = true;
  bool buttonIsPressed = (digitalRead(buttonPin) == LOW);
  if (buttonWasReleased && buttonIsPressed) {
    buzzer.stopBuzzer();
    buttonWasReleased = false;
  } else if (!buttonIsPressed) {
    buttonWasReleased = true;
  }

  if (buzzer.isActive()) {
    buzzer.updateBuzzer();
  }
  
 

  delay(40);
}
