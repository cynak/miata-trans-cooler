#include "Button.h"

Button::Button(int buttonPin, unsigned long debounce, unsigned long doublePressTime, unsigned long longPressTime)
  : pin(buttonPin), lastPressTime(0), pressDuration(0), isPressed(false), 
    debounceDelay(debounce), doublePressWindow(doublePressTime), longPressDuration(longPressTime), state(0) {
  pinMode(pin, INPUT);
}

void Button::update() {
  bool currentState = digitalRead(pin);
  unsigned long currentTime = millis();

  if (currentState && !isPressed && (currentTime - lastPressTime > debounceDelay)) {
    isPressed = true;
    pressDuration = currentTime;
  } else if (!currentState && isPressed) {
    isPressed = false;
    unsigned long pressTime = currentTime - pressDuration;
    if (pressTime >= longPressDuration) {
      state = 3; // Long press
    } else if (currentTime - lastPressTime < doublePressWindow) {
      state = 2; // Double press
    } else {
      state = 1; // Single press
    }
    lastPressTime = currentTime;
  }

  if (isPressed && (currentTime - pressDuration >= longPressDuration)) {
    state = 3; // Long press while still holding
  }
}

int Button::getState() {
  int currentState = state;
  state = 0; // Reset state after reading
  return currentState;
}
