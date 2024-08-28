#ifndef OLED_DRIVER_H
#define OLED_DRIVER_H

#include <stdint.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <avr/pgmspace.h>
#include "Constants.h"

class OLED_Driver {
    public:
        OLED_Driver(int rstPin, int dcPin, int csPin, int sclkPin, int dinPin);
        OLED_Driver(int rstPin, int dcPin, int csPin, int sclkPin, int dinPin, 
                    int mode, int x_window_size, int y_window_size);
        void init();
        void reset();
        void clear();
        void show(const UBYTE *Image);
        void updatePartial(const UBYTE *Image, UBYTE Xstart, UBYTE Ystart, UBYTE Xend, UBYTE Yend);
        
        
    private:
        int _rstPin, _dcPin, _csPin, _sclkPin, _dinPin, _mode, x_window_size, y_window_size;

        void OLED_InitReg();
        void OLED_WriteReg(uint8_t Reg);
        void OLED_WriteData(uint8_t Data);
        void OLED_SetWindow(uint8_t Xstart, uint8_t Ystart, uint8_t Xend, uint8_t Yend);
        void SPI4W_Write_Byte(uint8_t DATA);
        void I2C_Write_Byte(uint8_t value, uint8_t Cmd);
};

#endif
