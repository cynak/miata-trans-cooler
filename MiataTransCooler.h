#ifndef MIATATRANSCOOLER_H
#define MIATATRANSCOOLER_H

#include "Pump.h"
#include "Fan.h"
#include "AEMThermo.h"
#include "MultiButton.h"
#include "Button.h"

class MiataTransCooler
{
private:
    Pump pump;
    Fan fan;
    AEMThermo thermo;
    MultiButton uiControl;
    Button powerButton;
    int fanTemp;
    int pumpTemp;
    int fanSpeed;
    int pumpSpeed;
    int fanMaxSpeed;
    int pumpMaxSpeed;
    int fanMinSpeed;
    int pumpMinSpeed;
    int fanIncrement;
    int pumpIncrement;
    int fanRampUpTime;
    int pumpRampUpTime;
    int fanRampDownTime;
    int pumpRampDownTime;

public:
    MiataTransCooler(int pumpPin1, int pumpPin2, int fanPin1, int fanPin2,
                     int pumpControlPin, int fanControlPin, int thermoPin, int multiButtonPin,
                     int powerButtonPin, int fanMax, int pumpMax, int fanMin, int pumpMin, int fanInc,
                     int pumpInc, int fanRampUp, int pumpRampUp, int fanRampDown, int pumpRampDown);

    void update();
};

#endif
