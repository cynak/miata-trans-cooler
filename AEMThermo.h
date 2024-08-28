#ifndef AEMTHERMO_H
#define AEMTHERMO_H

#include <Arduino.h>

class AEMThermo {
public:
    // Constructor with optional resistor value parameter and temperature type
    AEMThermo(int pin, float resistorValue = 2200.0, bool fahrenheit = false);

    // Method to read voltage from the sensor
    float readVoltage();

    // Method to get the temperature
    float getTemperature();

    // Method to set the temperature type
    void setTempType(bool tempType);

    // Method to get the temperature type
    bool getTempType();

private:
    int analogPin; // Analog pin for the thermistor
    float R1; // Resistor value
    bool fahrenheit; // Temperature type flag

    // Method to interpolate temperature based on resistance
    float interpolateTemperature(float resistance);

    // Method to calculate the resistance of the thermistor
    float getResistance();

    // Method to convert Celsius to Fahrenheit
    float convertToFahrenheit(float celsiusTemp);

    // Calibration data: {temperature in C, resistance in ohms}
    static const float calibrationData[18][2];
    static const float Vcc; // Supply voltage
};

#endif // AEMTHERMO_H
