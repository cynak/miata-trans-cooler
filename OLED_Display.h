#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H
#include <stdint.h>
#include "OLED_Driver.h"

typedef uint8_t UBYTE;
typedef uint16_t UWORD;
class OLED_Display {
public:
    // Constructor with pin configuration
    OLED_Display(int rstPin, int dcPin, int csPin, int sclkPin, int dinPin);

    OLED_Display(int rstPin, int dcPin, int csPin, int sclkPin, int dinPin, int mode, int x_window_size,  int y_window_size);

    // Initialize the display
    void init();
    void reset();

    // Display multiple lines of text
    void displayText(const char* text[], int lines);

    // Draw a simple graph (example: line graph)
    void drawGraph(int data[], int dataSize);
    
    // Display an image
    void displayImage(const unsigned char* image);

private:
    int _rstPin, _dcPin, _csPin, _sclkPin, _dinPin, mode, x_window_size, y_window_size;
    OLED_Driver driver = OLED_Driver( _rstPin, _dcPin, _csPin, _sclkPin, _dinPin);
    UWORD ImageSize = (x_window_size /2) * y_window_size;
    UBYTE *Image = (UBYTE *)malloc(ImageSize/8);//Create a black image to clear the screen

    void clear();

    void OLED_InitReg();

    void OLED_WriteReg(uint8_t Reg);
    void OLED_WriteData(uint8_t Data);
};

#endif // OLED_DISPLAY_H
