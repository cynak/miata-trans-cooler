#ifndef PUMP_H
#define PUMP_H

#include "L298Controller.h"

class Pump : public L298Controller
{
public:
    Pump(int in1Pin, int in2Pin, int enaPin) : L298Controller(in1Pin, in2Pin, enaPin) {}
    // Additional functionality specific to Pump can be added here
};

#endif
