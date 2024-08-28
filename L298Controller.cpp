#include "L298Controller.h"

bool L298Controller::timerInitialized = false;

L298Controller::L298Controller(int in1Pin, int in2Pin, int enaPin)
  : in1(in1Pin), in2(in2Pin), ena(enaPin), in1_state(LOW), in2_state(LOW), ena_state(LOW), direction(1) {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ena, OUTPUT);

  // Initialize TimerOne only once
  if (!timerInitialized) {
    Timer1.initialize(100); // Set the period in microseconds (e.g., 100us for 10kHz)
    timerInitialized = true;
  }

  analogWrite(ena, 0); // Start with 0% duty cycle
}

void L298Controller::writeState() {
  digitalWrite(in1, in1_state);
  digitalWrite(in2, in2_state);
  analogWrite(ena, ena_state);
}

void L298Controller::off() {
  in1_state = LOW;
  in2_state = LOW;
  ena_state = LOW;
  writeState();
}

void L298Controller::on() {
  in1_state = HIGH;
  in2_state = LOW;
  writeState();
}

void L298Controller::fullSpeed() {
  switch(direction) {
    case 1: // forward
      in1_state = HIGH;
      in2_state = LOW;
      ena_state = 255;
      break;
    case -1: // reverse
      in1_state = LOW;
      in2_state = HIGH;
      ena_state = 255;
      break;
  }
  writeState();
}

void L298Controller::setSpeed(int speed) {
  if (speed < 0) speed = 0;
  if (speed > 255) speed = 255;
  ena_state = speed;
  writeState();
}

void L298Controller::setDirection(int dir) {
  direction = dir;
}

void L298Controller::setForward() {
  setDirection(1);
  in1_state = HIGH;
  in2_state = LOW;
  writeState();
}

void L298Controller::setReverse() {
  setDirection(-1);
  in1_state = LOW;
  in2_state = HIGH;
  writeState();
}

bool L298Controller::isOn() {
  return (in1_state == HIGH || in2_state == HIGH);
}

int L298Controller::getSpeed() {
  return ena_state;
}

int L298Controller::getDirection() {
  return direction;
}
