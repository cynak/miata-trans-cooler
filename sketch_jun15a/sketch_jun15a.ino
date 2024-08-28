#define FAN_ON_TEMP  210
#define FAN_OFF_TEMP  180
#define PUMP_MAX_FAN_ON_TEMP  220
#define PUMP_MIN_FAN_ON_TEMP  205
#define PUMP_MAX_FAN_ON_SPEED  100
#define PUMP_MIN_FAN_ON_SPEED  50
#define FAN_CONTROL_PIN  9
#define FAN_IN_PIN_1  7
#define FAN_IN_PIN_2  8
#define PUMP_IN_PIN_1  13
#define PUMP_IN_PIN_2  12
#define PUMP_CONTROL_PIN  11


class Pump {
  private:
    int enablePin; // PWM pin to control speed
    int controlPin1; // Control pin 1 to turn the pump on or off
    int controlPin2; // Control pin 2 to turn the pump on or off
    bool isOn;
    int speed;

  public:
    Pump(int enPin, int cPin1, int cPin2) 
      : enablePin(enPin), controlPin1(cPin1), controlPin2(cPin2), isOn(false), speed(0) {
        pinMode(enablePin, OUTPUT);
        pinMode(controlPin1, OUTPUT);
        pinMode(controlPin2, OUTPUT);
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, LOW);
    }

    void turnOn() {
        digitalWrite(controlPin1, HIGH);
        digitalWrite(controlPin2, LOW);
        isOn = true;
    }

    void turnOff() {
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, LOW);
        isOn = false;
        speed = 0;
        analogWrite(enablePin, speed);
    }

    void setSpeed(int newSpeed) {
        if (newSpeed < 0) newSpeed = 0;
        if (newSpeed > 255) newSpeed = 255;
        speed = newSpeed;
        if (isOn) {
            analogWrite(enablePin, speed);
        }
    }

    int getSpeed() {
        return speed;
    }

    bool isPumpOn() {
        return isOn;
    }
    //Function to be called in the loop
    void update(){

    }
};

class Fan {
  private:
    int enablePin; // PWM pin to control speed
    int controlPin1; // Control pin 1 to turn the fan on or off
    int controlPin2; // Control pin 2 to turn the fan on or off
    bool isOn;
    int speed;

  public:
    Fan(int enPin, int cPin1, int cPin2) 
      : enablePin(enPin), controlPin1(cPin1), controlPin2(cPin2), isOn(false), speed(0) {
        pinMode(enablePin, OUTPUT);
        pinMode(controlPin1, OUTPUT);
        pinMode(controlPin2, OUTPUT);
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, LOW);
    }

    void turnOn() {
        digitalWrite(controlPin1, HIGH);
        digitalWrite(controlPin2, LOW);
        isOn = true;
    }

    void turnOff() {
        digitalWrite(controlPin1, LOW);
        digitalWrite(controlPin2, LOW);
        isOn = false;
        speed = 0;
        analogWrite(enablePin, speed);
    }

    void setSpeed(int newSpeed) {
        if (newSpeed < 0) newSpeed = 0;
        if (newSpeed > 255) newSpeed = 255;
        speed = newSpeed;
        if (isOn) {
            analogWrite(enablePin, speed);
        }
    }

    int getSpeed() {
        return speed;
    }

    bool isFanOn() {
        return isOn;
    }
     //Function to be called in the loop
    void update(){

    }
};

class Thermistor {
  private:
    int analogPin; // Analog pin connected to the junction of the thermistor and the resistor
    const float Vcc = 5.0; // Supply voltage
    const float R1 = 2200.0; // Known resistor value (in ohms)

    // Calibration data: {temperature in C, resistance in ohms}
    const float calibrationData[18][2] = {
      {-20, 28136}, {-10, 15813}, {0, 9319}, {10, 5589}, {20, 3476}, {30, 2230},
      {40, 1466}, {50, 984}, {60, 671}, {70, 468}, {80, 332}, {90, 239},
      {100, 175}, {110, 129}, {120, 97}, {130, 73}, {140, 57}, {150, 43}
    };

    float readVoltage() {
      int sensorValue = analogRead(analogPin); // Read the analog input
      return sensorValue * (Vcc / 1023.0); // Convert the analog reading to voltage
    }

    float interpolateTemperature(float resistance) {
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

  public:
    Thermistor(int pin) : analogPin(pin) {}

    float getResistance() {
      float Vout = readVoltage();
      return R1 * (Vcc - Vout) / Vout;
    }

    float getTemperature() {
      float resistance = getResistance();
      return interpolateTemperature(resistance);
    }
};

class MiataTransCooler{
  Thermistor thermo;
  Pump pump;
  Fan fan;
  float currentTemp = 0;

  public:
    MiatTransCooler(int fan_in_1,int fan_in_2,int fin_ctrl,int pump_in_1, int pump_in_2, int pump_ctrl ){
      pump = Pump(pump_ctrl, pump_in_1, pump_in_2);
    };
    void update(){
      currentTemp=thermo.getTemperature();

    };
};


