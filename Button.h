#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
  private:
    int pin;
    unsigned long lastPressTime;
    unsigned long pressDuration;
    bool isPressed;
    unsigned long debounceDelay;
    unsigned long doublePressWindow;
    unsigned long longPressDuration;
    int state; // 1: single press, 2: double press, 3: long press

  public:
    Button(int buttonPin, unsigned long debounce = 50, unsigned long doublePressTime = 500, unsigned long longPressTime = 1000);
    void update();
    int getState();
};

#endif
