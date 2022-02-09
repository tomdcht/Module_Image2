#include <iostream>
#include <assert.h>
#include "Image.h"

Image::Image(){
    dimx = 0;
    dimy = 0;
}

Image::Image(int dimensionX, int dimensionY){
    assert(dimensionX >= 0 && dimensionY >= 0);
    dimx = dimensionX;
    dimy = dimensionY;

    tab = new Pixel[dimensionX * dimensionY];
}

Image::~Image () {
    if(tab != nullptr){
        std::cout << "Appel du destructeur";
        delete this->tab;
        tab = nullptr;
        dimx = dimy = 0;
    }
}

Pixel Image::getPix(int x, int y) const{
    assert((x >= 0 && x <= dimx) && (y >= 0 && y <= dimy));
    assert(tab != nullptr);
    return tab[y*dimx + x];

}

void Image::setPix(int x, int y, Pixel couleur){
    assert((x >= 0 && x <= dimx) && (y >= 0 && y <= dimy));
    assert(tab != nullptr);
    tab[dimx*y + x] = couleur;
}

void Image::dessinerRectangle(int Xmin, int Ymin, int Xmax, int Ymax, Pixel couleur){
    assert((Xmin >= 0 && Xmax <= dimx) && (Ymin >= 0 && Ymax <= dimy));
    for(int i= Xmin; i<= Xmax; i++){
        for(int j= Ymin; j<= Ymax; j++){
            setPix(i, j, couleur);
        }
    }
}

void Image::effacer(Pixel couleur){
    assert(tab != nullptr);
    dessinerRectangle(0, 0, dimx, dimy, couleur);
}


void Image::testRegression(){
    std::cout << "Test de Regréssion" << std::endl;

    std::cout << "Création d'une image de dimension de 160 par 160" << std::endl;
    getchar();
    std::cout << "Ajout d'un Pixel rouge aux coordonnées 100,100" << std::endl;
    Pixel rouge(255,0,0);
    setPix(1, 1, rouge);
    getchar();
    std::cout << "Recupèration de la valeur du pixel 100,100" << std::endl;
    getPix(1,1);
    getchar();
    std::cout << "Coloriage  de l'image en bleu avec dessinerRectangle" << std::endl;
    Pixel bleu(0,0,255);
    dessinerRectangle(1,1,2,2, bleu);
    getchar();
    std::cout << "Vérification du coloriage de l'image en bleu avec getPix" << std::endl;
    getPix(2, 2);
    getchar();
    std::cout << "Effacement de l'image avec la couleur blanche" << std::endl;
    Pixel blanc(255,255,255);
    effacer(blanc);
    getchar();

    /*std::cout << "Appel au destructeur sur im1" << std::endl;
    im.~Image();*/

    std::cout << "Fin du test de regréssion" << std::endl;
}
