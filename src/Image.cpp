/**
 * \file Image.cpp
 * \brief Créations des fonctions et procédures de Image.
 * \author DE CLERCQ.A et DECHANET.T
 * \version 1.0
 * \date 8 février 2022
 * \include Image.h
 */


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

Image::Image(unsigned int dimensionX, unsigned int dimensionY){
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

    window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH_WINDOW, HEIGHT_WINDOW, 0);
    if(!window){
        cout << "Erreur lors de la création de l'image ! " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 112, 114, 110, 255);
    SDL_RenderClear(renderer);
    if (renderer == NULL){
        cout << "Erreur lors de la création du renderer ! " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    picture = IMG_Load("data/im.pnm");
    if(!picture){
        cout << "Erreur concernant le chargement de l'image ! " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    texture = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);
    if(!texture){
        cout << "Erreur concernant la création de la texture ! " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if(SDL_QueryTexture(texture, NULL, NULL, &dest_rect.w, &dest_rect.h) != 0){
        cout << "Erreur lors de l'application de la texture ! " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if(SDL_RenderCopy(renderer, texture, &src_rect, &dest_rect) != 0){
        cout << "Erreur lors de l'application du rendu ! " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    SDL_RenderPresent(renderer);

}

void Image::SDL_ZoomIn(SDL_Rect rect){
    SDL_Rect new_rect = {WIDTH_WINDOW/2 - rect.w/2, HEIGHT_WINDOW/2 - rect.h/2, rect.w + 10, rect.h + 10};
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, &src_rect, &new_rect);
    SDL_RenderPresent(renderer);
    dest_rect = new_rect;
}

void Image::SDL_ZoomOut(SDL_Rect rect){
    SDL_Rect new_rect = {WIDTH_WINDOW/2 - rect.w/2, HEIGHT_WINDOW/2 - rect.h/2, rect.w - 10, rect.h - 10};
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, &src_rect, &new_rect);
    SDL_RenderPresent(renderer);
    dest_rect = new_rect;
}

void Image::SDLAffLoop(){
    SDL_Event events;
	bool quit = false;

    while (!quit) {
        while(SDL_PollEvent(&events)){
            switch (events.type) {
                case SDL_KEYDOWN:
                    if(events.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                        cout << "Fermeture de la fenêtre" << endl;
                        SDLAffQuit();
                        quit = true; break;
                    }

                    if(events.key.keysym.scancode == SDL_SCANCODE_T){
                        SDL_ZoomIn(dest_rect);
                        cout << "Zoom In" << endl;
                    }

                    if(events.key.keysym.scancode == SDL_SCANCODE_G){
                        SDL_ZoomOut(dest_rect);
                        cout << "Zoom Out" << endl;
                    }
                    break;

                case SDL_KEYUP:

                case SDL_WINDOWEVENT:
                    if (events.window.event == SDL_WINDOWEVENT_CLOSE)
                        quit = true; break;
            }
        }
    }
}

void Image::SDLAffQuit(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(picture);
    SDL_Quit();
}

void Image::afficher(){

    sauver("data/im.pnm");
    SDLAffInit();
    SDLAffLoop();
}