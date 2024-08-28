#include "MiataTransCooler.h"

MiataTransCooler::MiataTransCooler(int pumpPin1, int pumpPin2, int fanPin1, int fanPin2,
                                   int pumpControlPin, int fanControlPin, int thermoPin, int multiButtonPin,
                                   int powerButtonPin, int fanMax, int pumpMax, int fanMin, int pumpMin, int fanInc,
                                   int pumpInc, int fanRampUp, int pumpRampUp, int fanRampDown, int pumpRampDown)
    : pump(pumpPin1, pumpPin2, pumpControlPin), fan(fanPin1, fanPin2, fanControlPin),
      thermo(thermoPin), uiControl(multiButtonPin, 3, new int[3]{0, 1, 2}), powerButton(powerButtonPin),
      fanMaxSpeed(fanMax), pumpMaxSpeed(pumpMax), fanMinSpeed(fanMin), pumpMinSpeed(pumpMin),
      fanIncrement(fanInc), pumpIncrement(pumpInc), fanRampUpTime(fanRampUp), pumpRampUpTime(pumpRampUp),
      fanRampDownTime(fanRampDown), pumpRampDownTime(pumpRampDown)
{
}

void MiataTransCooler::update() {
    Serial.println(uiControl.getState());
}
