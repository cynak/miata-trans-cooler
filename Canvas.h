
#include "Constants.h"


class Canvas
{  
    UBYTE *Image;
    int *WIDTH;
    int *HEIGHT;
    int *ROTATE;

    

    public:
        void clearImage();
        void drawLine(int x1, int y1, int x2, int y2);
        void drawRectangle(int x1, int y1, int x2, int y2);
        void drawCircle(int x, int y, int r);
        void drawText(const char* text, int x, int y);
        void drawImage(const unsigned char* image);
        void update();
    private:

 }   ;