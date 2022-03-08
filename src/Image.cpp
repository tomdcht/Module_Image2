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
    if(tab != NULL){
        delete [] this->tab;
        tab = nullptr;
        dimx = dimy = 0;
    }
}

Pixel& Image::getPix(const unsigned int x, const unsigned int y) const{
    assert((x >= 0 && x <= dimx) && (y >= 0 && y <= dimy));
    assert((y*dimx + x) < dimx * dimy);
    assert(tab != nullptr);
    return tab[y*dimx + x];
}

void Image::setPix(const unsigned int x, const unsigned int y, const Pixel& couleur) const{
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

    //test constructeur sans paramètre
    //post conditon coordonnées égale à 0 + n'alloue pas de pixel
    Image im1;
    assert(im1.dimx == 0 && im1.dimy == 0 && im1.tab == nullptr);

    //test constucteur avec paramètre
    //post condition x,y initialiser + tableau de pixel alloué
    Image im2(4, 4);
    Pixel unPixel = im2.getPix(1,1);
    assert(unPixel.getRouge()==0 && unPixel.getVert()==0 && unPixel.getBleu()==0); //vérifie que les pixels sont bien noir
    assert(im2.tab != nullptr); //tab non vide -> bien alloué

    //test setPix, getPix
    //Post condition setPix -> pixel de coodronnée (x,y) modifer
    //Post condition getPix -> recupere le pixel de coordonné (x,y)
    Pixel rouge(255,0,0);
    im2.setPix(1,2,rouge);
    unPixel = im2.getPix(1,2);
    assert(unPixel.getRouge()==255); //ok pixel (1,2) rouge

    //test dessinerRectangle
    // Post conditon: création d'une retangle de couleur au coordonné Xmin,Ymin Xmax,Ymax compris
    Pixel bleu(0,0,255);
    im2.dessinerRectangle(0,0,4,4,bleu);
    unPixel = im2.getPix(0,0);
    assert(unPixel.getBleu()==255); //test si indice de paramètre compris
    Pixel unAutrePixel = im2.getPix(3,3);
    assert(unAutrePixel.getBleu()==255);

    //test effacer
    // Post condition: image initial effacer et remplacer par un nouveau fond de couleur
    im2.effacer(rouge);
    unPixel = im2.getPix(0,0);
    unAutrePixel = im2.getPix(3,3);
    assert(unPixel.getRouge()==255);
    assert(unAutrePixel.getRouge()==255);
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
    SDL_Rect new_rect = {WIDTH_WINDOW/2 - dest_rect.w/2, HEIGHT_WINDOW/2 - dest_rect.h/2, rect.w + 10, rect.h + 10};
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, &src_rect, &new_rect);
    SDL_RenderPresent(renderer);
    dest_rect = new_rect;
}

void Image::SDL_ZoomOut(SDL_Rect rect){
    SDL_Rect new_rect = {WIDTH_WINDOW/2 - dest_rect.w/2, HEIGHT_WINDOW/2 - dest_rect.h/2, rect.w - 10, rect.h - 10};
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
                    }

                    if(events.key.keysym.scancode == SDL_SCANCODE_G){
                        SDL_ZoomOut(dest_rect);
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