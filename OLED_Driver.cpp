#include "OLED_Driver.h"


OLED_Driver::OLED_Driver(int rstPin, int dcPin, int csPin, int sclkPin, int dinPin) :
    _rstPin(rstPin), _dcPin(dcPin), _csPin(csPin), _sclkPin(sclkPin), _dinPin(dinPin), _mode(USE_SPI_4W), 
    x_window_size(128), y_window_size(128) {}

OLED_Driver::OLED_Driver(int rstPin, int dcPin, int csPin, int sclkPin, int dinPin, int mode, int x_window_size, int y_window_size) :
    _rstPin(rstPin), _dcPin(dcPin), _csPin(csPin), _sclkPin(sclkPin), _dinPin(dinPin), _mode(mode), 
    x_window_size(x_window_size), y_window_size(y_window_size) {}


void OLED_Driver::init()
{
    pinMode(_rstPin, OUTPUT);
    pinMode(_dcPin, OUTPUT);
    pinMode(_csPin, OUTPUT);
    pinMode(_sclkPin, OUTPUT);
    pinMode(_dinPin, OUTPUT);
    reset();
    OLED_InitReg();
    clear();
}

void OLED_Driver::clear()
{
    UWORD i;
    OLED_SetWindow(0, 0, 128, 128);
    for(i=0; i<x_window_size*y_window_size/2; i++){
        OLED_WriteData(0x00);
    }
}

void OLED_Driver::show(const UBYTE *Image){
    UWORD i, j, temp;
    OLED_SetWindow(0, 0, x_window_size, y_window_size);
    for(i=0; i<y_window_size; i++)
        for(j=0; j<x_window_size/2; j++)
        {
            temp = pgm_read_byte(&Image[j + i*64]);
            OLED_WriteData(temp);
        }
}
void OLED_Driver::updatePartial(const UBYTE *Image, UBYTE Xstart, UBYTE Ystart, UBYTE Xend, UBYTE Yend)
{
    UWORD i, j, temp;

    if ((Xstart > x_window_size) || (Ystart > y_window_size) || (Xend > x_window_size) || (Yend > y_window_size))
        return Serial.println("Invalid coordinates to update partial image");
    OLED_SetWindow(Xstart, Ystart, Xend, Yend);
    for(i=0; i<Yend-Ystart; i++)
        for(j=0; j<(Xend-Xstart)/2; j++)
        {
            temp = Image[j + i*(Xend-Xstart)/2];
            OLED_WriteData(temp);
        }
}

void OLED_Driver::reset()
{
    digitalWrite(_rstPin, HIGH);
    delay(100);
    digitalWrite(_rstPin, LOW);
    delay(100);
    digitalWrite(_rstPin, HIGH);
    delay(100);
}

void OLED_Driver::OLED_InitReg()
{
    OLED_WriteReg(0xae); //--turn off oled panel

    OLED_WriteReg(0x15); // set column address
    OLED_WriteReg(0x00); // start column   0
    OLED_WriteReg(0x7f); // end column   127

    OLED_WriteReg(0x75); // set row address
    OLED_WriteReg(0x00); // start row   0
    OLED_WriteReg(0x7f); // end row   127

    OLED_WriteReg(0x81); // set contrast control
    OLED_WriteReg(0x80);

    OLED_WriteReg(0xa0); // segment remap
    OLED_WriteReg(0x51); // 51

    OLED_WriteReg(0xa1); // start line
    OLED_WriteReg(0x00);

    OLED_WriteReg(0xa2); // display offset
    OLED_WriteReg(0x00);

    OLED_WriteReg(0xa4); // normal display
    OLED_WriteReg(0xa8); // set multiplex ratio
    OLED_WriteReg(0x7f);

    OLED_WriteReg(0xb1); // set phase length
    OLED_WriteReg(0xf1);

    OLED_WriteReg(0xb3); // set dclk
    OLED_WriteReg(0x00); // 80Hz:0xc1 90Hz:0xe1 100Hz:0x00 110Hz:0x30 120Hz:0x50 130Hz:0x70 01

    OLED_WriteReg(0xab);
    OLED_WriteReg(0x01);

    OLED_WriteReg(0xb6); // set phase length
    OLED_WriteReg(0x0f);

    OLED_WriteReg(0xbe);
    OLED_WriteReg(0x0f);

    OLED_WriteReg(0xbc);
    OLED_WriteReg(0x08);

    OLED_WriteReg(0xd5);
    OLED_WriteReg(0x62);

    OLED_WriteReg(0xfd);
    OLED_WriteReg(0x12);
}

void OLED_Driver::OLED_SetWindow(uint8_t Xstart, uint8_t Ystart, uint8_t Xend, uint8_t Yend)
{
    if ((Xstart > x_window_size) || (Ystart > y_window_size) || (Xend > x_window_size) || (Yend > y_window_size))
        return;

    OLED_WriteReg(0x15);
    OLED_WriteReg(Xstart / 2);
    OLED_WriteReg(Xend / 2 - 1);

    OLED_WriteReg(0x75);
    OLED_WriteReg(Ystart);
    OLED_WriteReg(Yend - 1);
}

void OLED_Driver::OLED_WriteReg(uint8_t Reg)
{
    if (_mode == USE_SPI_4W)
    {
        digitalWrite(_dcPin, 0);
        digitalWrite(_csPin,0);
        SPI4W_Write_Byte(Reg);
        digitalWrite(_csPin,1);

    }
    else
    {
        I2C_Write_Byte(Reg, IIC_CMD);
    }
}

void OLED_Driver::OLED_WriteData(uint8_t Data)
{
    if (_mode == USE_SPI_4W)
    {
        digitalWrite(_dcPin, 1);
        digitalWrite(_csPin,0);
        SPI4W_Write_Byte(Data);
        digitalWrite(_csPin,0);
    }
    else
    {
        I2C_Write_Byte(Data, IIC_RAM);
    }
}


void OLED_Driver::SPI4W_Write_Byte(uint8_t DATA)
{
    SPI.transfer(DATA);
}

void OLED_Driver::I2C_Write_Byte(uint8_t value, uint8_t Cmd)
{
    uint8_t Addr = 0x3c;
    Wire.beginTransmission(Addr);
    Wire.write(Cmd);
    Wire.write(value);
    Wire.endTransmission();
}
