#ifndef MYO_H
#define MYO_H

#include <myo.h>

extern armband myo;

int getImuData();
int getEmgData();
void myo_connect();

#endif
