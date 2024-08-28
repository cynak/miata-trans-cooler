#ifndef FAN_H
#define FAN_H

#include "L298Controller.h"

class Fan : public L298Controller
{
public:
    Fan(int in1Pin, int in2Pin, int enaPin) : L298Controller(in1Pin, in2Pin, enaPin) {}
    // Additional functionality specific to Fan can be added here
};

#endif
