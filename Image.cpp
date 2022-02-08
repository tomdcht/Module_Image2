#include <iostream>
#include "Image.h"

Image::Image(){
    dimx = 0;
    dimy = 0;
}

Image::Image(int dimensionX, int dimensionY){
    assert(dimensionX != NULL && dimensionY != NULL);
    dimensionX = dimx;
    dimensionY = dimy;

    tab = new Pixel[];

}