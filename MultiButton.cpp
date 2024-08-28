#include "MultiButton.h"

MultiButton::MultiButton(int buttonPin, int buttons, int* values, unsigned long debounce, unsigned long doublePressTime, unsigned long longPressTime)
  : pin(buttonPin), numButtons(buttons), buttonValues(values), lastPressTime(0), pressDuration(0), isPressed(false), 
    debounceDelay(debounce), doublePressWindow(doublePressTime), longPressDuration(longPressTime), state(0), currentButton(-1) {
  pinMode(pin, INPUT);
}

void MultiButton::update() {
  int analogValue = analogRead(pin);
  unsigned long currentTime = millis();
  int button = -1;

  // Determine which button is pressed based on the analog value
  for (int i = 0; i < numButtons; i++) {
    if (analogValue >= buttonValues[i] - 10 && analogValue <= buttonValues[i] + 10) { // Adjust the range as necessary
      button = i;
      break;
    }
  }

  if (button != -1 && !isPressed && (currentTime - lastPressTime > debounceDelay)) {
    isPressed = true;
    pressDuration = currentTime;
    currentButton = button;
  } else if (button == -1 && isPressed) {
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

int MultiButton::getButton() {
  return currentButton;
}

int MultiButton::getState() {
  int currentState = state;
  state = 0; // Reset state after reading
  return currentState;
}
