#ifndef DFPLAYER_COMMANDS_H
#define DFPLAYER_COMMANDS_H

#include <Arduino.h>

#define RXD2 26
#define TXD2 27
#define BUTTON_PIN 2 

void sendDFCommand(byte Command, int ParData);
void playTrack(int tracknum);
void playNext();
void volumeUp();
void volumeDown();
void changeVolume(int thevolume);
void handleSerialCommunication();

extern int q;
extern byte returnCodes[10];
extern byte returnByteCounter;

#endif
