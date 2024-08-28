#include "AEMThermo.h"

const float AEMThermo::Vcc = 5.0;

// Calibration data: {temperature in C, resistance in ohms}
const float AEMThermo::calibrationData[18][2] = {
  {-20, 28136}, {-10, 15813}, {0, 9319}, {10, 5589}, {20, 3476}, {30, 2230},
  {40, 1466}, {50, 984}, {60, 671}, {70, 468}, {80, 332}, {90, 239},
  {100, 175}, {110, 129}, {120, 97}, {130, 73}, {140, 57}, {150, 43}
};

// Constructor with optional resistor value parameter and temperature type
AEMThermo::AEMThermo(int pin, float resistorValue, bool fahrenheit) 
  : analogPin(pin), R1(resistorValue), fahrenheit(fahrenheit) {}

float AEMThermo::readVoltage() {
  int sensorValue = analogRead(analogPin); // Read the analog input
  return sensorValue * (Vcc / 1023.0); // Convert the analog reading to voltage
}

void AEMThermo::setTempType(bool tempType){
  fahrenheit = tempType;
}

float AEMThermo::interpolateTemperature(float resistance) {
  for (int i = 0; i < 17; i++) {
    if (resistance > calibrationData[i][1]) {
      float R1 = calibrationData[i][1];
      float R2 = calibrationData[i + 1][1];
      float T1 = calibrationData[i][0];
      float T2 = calibrationData[i + 1][0];
      return T1 + (T2 - T1) * (resistance - R1) / (R2 - R1);
    }
  }
  return calibrationData[17][0]; // Return the highest temperature if resistance is very low
}

float AEMThermo::convertToFahrenheit(float celsiusTemp){
  return (celsiusTemp * 9.0/5.0) + 32;
}

float AEMThermo::getResistance() {
  float Vout = readVoltage();
  return R1 * (Vcc - Vout) / Vout;
}

bool AEMThermo::getTempType(){
  return fahrenheit;
}

float AEMThermo::getTemperature() {
  float resistance = getResistance();
  float temperature = interpolateTemperature(resistance);
  if (fahrenheit) {
    return convertToFahrenheit(temperature);
  } else {
    return temperature;
  }
}
