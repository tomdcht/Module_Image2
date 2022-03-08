/**
 * \file Pixel.cpp
 * \brief Créations des fonctions et procédures de Pixel.
 * \author DE CLERCQ.A et DECHANET.T
 * \version 1.0
 * \date 8 février 2022
 */

#include "Pixel.h"
#include <iostream>

using namespace std;

Pixel::Pixel(){
    r = 0;
    g = 0;
    b = 0;
}

Pixel::Pixel(const int nr ,const int ng,const int nb) {
    r = nr;
    g = ng;
    b = nb;
}

unsigned char Pixel::getRouge () const {
    return r;
}

unsigned char Pixel::getVert () const  {
    return g;
}

unsigned char Pixel::getBleu () const{
    return b;
}

void Pixel::setRouge(unsigned int nr) {
    r = nr;
}

void Pixel::setVert(unsigned int ng) {
    g = ng;
}

void Pixel::setBleu(unsigned int nb) {
    b = nb;
}
