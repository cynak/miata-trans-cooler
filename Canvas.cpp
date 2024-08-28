#include "Canvas.h"


void Canvas::clearImage(){
    for(int i = 0; i < *WIDTH * *HEIGHT; i++){
        Image[i] = 0x00;
    };
};

