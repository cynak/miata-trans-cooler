#ifndef MULTIBUTTON_H
#define MULTIBUTTON_H

#include <Arduino.h>

class MultiButton {
  private:
    int pin;
    int numButtons;
    int* buttonValues; // Array to hold the analog values corresponding to each button
    unsigned long lastPressTime;
    unsigned long pressDuration;
    bool isPressed;
    int currentButton;
    unsigned long debounceDelay;
    unsigned long doublePressWindow;
    unsigned long longPressDuration;
    int state; // 1: single press, 2: double press, 3: long press

  public:
    MultiButton(int buttonPin, int buttons, int* values, unsigned long debounce = 50, unsigned long doublePressTime = 500, unsigned long longPressTime = 1000);
    void update();
    int getButton();
    int getState();
};

#endif
