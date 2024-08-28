#include <Arduino.h>
// #include "Button.h"
// #include "L298Controller.h"
// #include "AEMThermo.h"
// #include "MiataTransCooler.h"
// #include "OLED_Display.h"
#include <U8g2lib.h>
#define PUMP_PIN_IN_1 1
#define PUMP_PIN_IN_2 2
#define FAN_PIN_IN_1 3
#define FAN_PIN_IN_2 4
#define PUMP_CONTROL_PIN 6
#define FAN_CONTROL_PIN 5
#define MULTI_BUTTON_A_PIN A1
#define POWER_BUTTON_PIN A0
#define OLED_DIN 12
#define OLED_CLK 13
#define OLED_CS 4
#define OLED_DC 8
#define OLED_RST 7
AEMThermo thermo = NULL;
Button btn = NULL;

U8X8_SSD1327_MIDAS_128X128_4W_SW_SPI u8x8
    (/* clock=*/ 9, /* data=*/ 8, /* cs=*/ 10, /* dc=*/ 11, /* reset=*/ 12);
void setup(void)
{
  /* U8g2 Project: SSD1306 Test Board */
  //pinMode(10, OUTPUT);
  //pinMode(9, OUTPUT);
  //digitalWrite(10, 0);
  //digitalWrite(9, 0); 
  
  /* U8g2 Project: KS0108 Test Board */
  //pinMode(16, OUTPUT);
  //digitalWrite(16, 0); 
  
  u8x8.begin();
  u8x8.setPowerSave(0);
  
  
}