#include "DFPlayerCommands.h"

int q = 5;
byte returnCodes[10];
byte returnByteCounter;

void sendDFCommand(byte Command, int ParData) {
  byte commandData[10];
  byte q;
  int checkSum;
  Serial.print("Com: ");
  Serial.print(Command, HEX);
  commandData[0] = 0x7E;
  commandData[1] = 0xFF;
  commandData[2] = 0x06;
  commandData[3] = Command;
  commandData[4] = 0x01;
  commandData[5] = highByte(ParData);
  commandData[6] = lowByte(ParData);
  checkSum = -(commandData[1] + commandData[2] + commandData[3] + commandData[4] + commandData[5] + commandData[6]);
  commandData[7] = highByte(checkSum);
  commandData[8] = lowByte(checkSum);
  commandData[9] = 0xEF;
  for (q = 0; q < 10; q++) {
    Serial2.write(commandData[q]);
  }
  Serial.println("Command Sent: ");
  for (q = 0; q < 10; q++) {
    Serial.println(commandData[q], HEX);
  }
  Serial.println("End Command: ");
  delay(100);
}

void playTrack(int tracknum) {
  Serial.print("Track selected: ");
  Serial.println(tracknum);
  sendDFCommand(0x03, tracknum);
}

void playNext() {
  Serial.println("Play Next");
  sendDFCommand(0x01, 0);
}

void volumeUp() {
  Serial.println("Vol UP");
  sendDFCommand(0x04, 0);
}

void volumeDown() {
  Serial.println("Vol Down");
  sendDFCommand(0x05, 0);
}

void changeVolume(int thevolume) {
  sendDFCommand(0x06, thevolume);
}

void handleSerialCommunication() {
  byte readByte;
  while (Serial2.available()) {
    readByte = Serial2.read();
    Serial.print(readByte, HEX);
    Serial.print(" Count: ");
    Serial.println(returnByteCounter);

    if(returnByteCounter == 0) {
      if(readByte == 0x7E) {
        returnCodes[returnByteCounter] = readByte;
        returnByteCounter++;
      }
    } else {
      returnCodes[returnByteCounter] = readByte;
      returnByteCounter++; 
    }

    if(returnByteCounter > 9) {
      Serial.println("Code String");
      for(int w = 0; w < 10; w++) {
        Serial.print(returnCodes[w], HEX);  
        Serial.print(" ");  
      }
      Serial.println(" ");
      if(returnCodes[3] == 0x3D) { // track finished
        Serial.println("Play Next Track");
        playNext(); // play next track 
      }
      returnByteCounter = 0;
    }
  }
}
