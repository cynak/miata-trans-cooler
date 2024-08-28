#ifndef L298CONTROLLER_H
#define L298CONTROLLER_H

#include <Arduino.h>
#include <TimerOne.h>

class L298Controller {
  protected:
    int in1;
    int in2;
    int ena;
    int in1_state;
    int in2_state;
    int ena_state;
    int direction; // 1 forward, -1 reverse, 0 neutral
    static bool timerInitialized; // Static variable to check TimerOne initialization

  public:
    L298Controller(int in1Pin, int in2Pin, int enaPin);
    virtual void writeState();
    virtual void off();
    virtual void on();
    virtual void fullSpeed();
    virtual void setSpeed(int speed);
    virtual void setDirection(int dir);
    virtual void setForward();
    virtual void setReverse();
    virtual bool isOn();
    virtual int getSpeed();
    virtual int getDirection();
};

#endif
