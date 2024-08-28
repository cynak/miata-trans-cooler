#include "OLED_Display.h"
#include <Arduino.h>
typedef uint8_t UBYTE;
typedef uint16_t UWORD;
#define USE_SPI_4W 0
// Constructor with pin configuration
OLED_Display::OLED_Display(int rstPin, int dcPin, int csPin, int sclkPin, int dinPin)
    : _rstPin(rstPin), _dcPin(dcPin), _csPin(csPin), _sclkPin(sclkPin), _dinPin(dinPin) {}
OLED_Display::OLED_Display(int rstPin, int dcPin, int csPin, int sclkPin, int dinPin, int mode = USE_SPI_4W, int x_window_size = 128, int y_window_size = 128)
    : _rstPin(rstPin), _dcPin(dcPin), _csPin(csPin), _sclkPin(sclkPin), _dinPin(dinPin), mode(mode),
      x_window_size(x_window_size), y_window_size(y_window_size) {}

// Initialize the display
void OLED_Display::init()
{
    Serial.println("USE_SPI");
    // set OLED SPI
    SPI.setDataMode(SPI_MODE3);
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    SPI.begin();
    pinMode(_rstPin, OUTPUT);
    pinMode(_dcPin, OUTPUT);
    pinMode(_csPin, OUTPUT);
    pinMode(_sclkPin, OUTPUT);
    pinMode(_dinPin, OUTPUT);
    reset();
    OLED_InitReg();
    delay(200);
    OLED_WriteReg(0xAF);
}

void OLED_
// Clear the display
void OLED_Display::clear()
{
    //clear out all values in Image to 0
    for (int i = 0; i < ImageSize / 8; i++)
    {
        Image[i] = 0;
    }

    OLED_Display();
}

// Display multiple lines of text
void OLED_Display::displayText(const char *text[], int lines)
{
    clear();
    for (int i = 0; i < lines; i++)
    {
        Paint_DrawString_EN(0, i * 16, text[i], &Font16, WHITE, BLACK);
    }
    OLED_Display();
}

// Draw a simple graph
void OLED_Display::drawGraph(int data[], int dataSize)
{
    clear();
    for (int i = 0; i < dataSize - 1; i++)
    {
        Paint_DrawLine(i * (128 / dataSize), 128 - data[i], (i + 1) * (128 / dataSize), 128 - data[i + 1], WHITE, DOT_PIXEL_DFT, LINE_STYLE_SOLID);
    }
    OLED_Display();
}

// Display an image
void OLED_Display::displayImage(const unsigned char *image)
{
    clear();
    Paint_DrawImage(image, 0, 0, 128, 128);
    OLED_Display();
}
