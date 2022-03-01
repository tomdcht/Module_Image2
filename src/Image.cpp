#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>
#include "Image.h"
using namespace std;

Image::Image(){
    dimx = 0;
    dimy = 0;
    tab = nullptr;
}

Image::Image(int dimensionX, int dimensionY){
    assert(dimensionX > 0 && dimensionY > 0);
    dimx = dimensionX;
    dimy = dimensionY;

    tab = new Pixel[dimensionX * dimensionY];

    Pixel noir(0,0,0);

    for(int i = 0; i < dimensionX * dimensionY; i++){
        tab[i] = noir;
    }
}

Image::~Image () {
    if(tab != nullptr){
        std::cout << "Appel du destructeur";
        delete [] this->tab;
        tab = nullptr;
        dimx = dimy = 0;
    }
}

Pixel Image::getPix(unsigned int x, unsigned int y) const{
    assert((x >= 0 && x <= dimx) && (y >= 0 && y <= dimy));
    assert((y*dimx + x) < dimx * dimy);
    assert(tab != nullptr);
    return tab[y*dimx + x];
}

void Image::setPix(unsigned int x, unsigned int y, Pixel couleur){
    assert((x >= 0 && x <= dimx) && (y >= 0 && y <= dimy));
    assert(tab != nullptr);
    tab[y*dimx + x] = couleur;
}

void Image::dessinerRectangle(unsigned int Xmin, unsigned int Ymin, unsigned int Xmax, unsigned int Ymax, Pixel couleur){
    assert((Xmin >= 0 && Xmax <= dimx) && (Ymin >= 0 && Ymax <= dimy));
    for(unsigned int i = Xmin; i < Xmax; i++){
        for(unsigned int j=Ymin ; j < Ymax; j++){
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
    std::cout << "Recupèration de la valeur du pixel 1,1" << std::endl;
    getPix(1,1);
    getchar();
    std::cout << "Coloriage  de l'image en bleu avec dessinerRectangle" << std::endl;
    Pixel bleu(0,0,255);
    dessinerRectangle(1,1,2,2, bleu);
    getchar();
    std::cout << "Vérification du coloriage de l'image en bleu avec getPix" << std::endl;
    getPix(2, 1);
    getchar();
    std::cout << "Effacement de l'image avec la couleur blanche" << std::endl;
    Pixel blanc(255,255,255);
    effacer(blanc);
    getchar();

    /*std::cout << "Appel au destructeur sur im1" << std::endl;
    im.~Image();*/

    std::cout << "Fin du test de regréssion" << std::endl;
}


void Image::sauver(const string & filename) const {
    ofstream fichier (filename.c_str());
    assert(fichier.is_open());
    fichier << "P3" << endl;
    fichier << dimx << " " << dimy << endl;
    fichier << "255" << endl;
    for(unsigned int y=0; y<dimy; y++)
        for(unsigned int x=0; x<dimx; x++) {
            const Pixel pix = getPix(x,y);
            fichier << +pix.getRouge() << " " << +pix.getVert() << " " << +pix.getBleu() << " ";
        }
    cout << "Sauvegarde de l'image " << filename << " ... OK\n";
    fichier.close();
}

void Image::ouvrir(const string & filename) {
    ifstream fichier (filename.c_str());
    assert(fichier.is_open());
	unsigned int r,g,b;
	string mot;
	dimx = dimy = 0;
	fichier >> mot >> dimx >> dimy >> mot;
	assert(dimx > 0 && dimy > 0);
	if (tab != NULL) delete [] tab;
	tab = new Pixel [dimx*dimy];
    for(unsigned int y=0; y<dimy; y++)
        for(unsigned int x=0; x<dimx; x++) {
            fichier >> r >> g >> b;
            Pixel tmp(r,g,b);
            setPix(x, y, tmp);
        }
    fichier.close();
    cout << "Lecture de l'image " << filename << " ... OK\n";
}

void Image::afficherConsole(){
    cout << dimx << " " << dimy << endl;
    for(unsigned int y=0; y<dimy; ++y) {
        for(unsigned int x=0; x<dimx; ++x) {
            const Pixel& pix = getPix(x,y);
            cout << +pix.getRouge() << " " << +pix.getVert() <<  " " << +pix.getBleu() << " ";
        }
        cout << endl;
    }
}

//SDL

void Image::SDLAffInit(){

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 200, 200, 0);

    if(!window){
        cout << "Erreur lors de la création de l'image ! " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    window_surface = SDL_GetWindowSurface(window);

    if(!window_surface){
        cout << "Erreur concernant la surface de la fenêtre ! " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

}

void Image::SDLAffLoop(){
    SDL_Event events;
	bool quit = false;

    while (!quit) {
        if (events.type == SDL_QUIT) quit = true;
        else if (events.type == SDL_KEYDOWN) {
            switch (events.key.keysym.scancode) {
                case SDL_SCANCODE_T:
                case SDL_SCANCODE_G:
                case SDL_SCANCODE_ESCAPE:
                    quit = true; break;

            }
        }
    }
}




void Image::afficher(){

    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

    sauver("im.ppm");
    window_surface = IMG_Load("im.ppm");

    if (window_surface == NULL) {
        cout<<"Error: cannot load surface "<< endl;
        SDL_Quit();
        exit(1);
    }

    texture = SDL_CreateTextureFromSurface(renderer,window_surface);
    if (texture == NULL) {
        cout << "Error: problem to create the texture of image" << endl;
        SDL_Quit();
        exit(1);
    }

}