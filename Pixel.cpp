/**
 * \file Pixel.cpp
 * \brief Créations des fonctions et procédures de pixel.
 * \author DE CLERCQ.A et DECHANET.T
 * \version 1.0
 * \date 8 février 2022
 */

#include "Pixel.h"
#include <iostream>

using namespace std;

Pixel::Pixel(){ /// Constructeur par défaut de la classe: initialise le pixel à la couleur noire
    r = 0;
    g = 0;
    b = 0;
}

Pixel::Pixel(const int nr ,const int ng,const int nb) {   /// Constructeur de la classe: initialise r,g,b avec les paramètres
    r = nr;
    g = ng;
    b = nb;
}

int Pixel::getRouge () const { /// Accesseur : récupère la composante rouge du pixel
    return r;
}

int Pixel::getVert () const  { /// Accesseur : récupère la composante verte du pixel
    return g;
}

int Pixel::getBleu () const{ /// Accesseur : récupère la composante bleue du pixel
    return b;
}

void Pixel::setRouge(unsigned int nr) { /// Mutateur : modifie la composante rouge du pixel
    r = nr;
}

void Pixel::setVert(unsigned int ng) { /// Mutateur : modifie la composante vert du pixel
    g = ng;
}

void Pixel::setBleu(unsigned int nb) { /// Mutateur : modifie la composante bleu du pixel
    b = nb;
}
