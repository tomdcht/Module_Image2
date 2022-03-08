/**

* \file Image.h
* \brief Définition des donées membres et des fonctions membres de la classe Image
* \version 1.0
* \date 8 Février 2022
* \include Pixel.h

*/

#include <string>
#include "Pixel.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH_WINDOW 200
#define HEIGHT_WINDOW 200

/**
 * \class Image
 * \brief Class Image
 *
 * Déclaration des données membres et des fonctions de la class Image
 */

class Image {
    private:

        ///Tableau de pixels
        Pixel *tab;

        ///Dimensions de l'image
        unsigned int dimx, dimy;

        void SDLAffInit();
        void SDLAffLoop();
        void SDLAffQuit();

    public:
        SDL_Window * window;
        SDL_Renderer * renderer;
        SDL_Surface *picture;
        SDL_Texture *texture;
        SDL_Rect dest_rect = {WIDTH_WINDOW/2,HEIGHT_WINDOW/2,HEIGHT_WINDOW,HEIGHT_WINDOW};
        SDL_Rect src_rect = {0,0,10,10};

        /// Constructeur par défaut de la classe: initialise dimx et dimy à 0
        /// ce constructeur n'alloue pas de pixel
        Image ();

        /// Constructeur de la classe: initialise dimx et dimy (après vérification)
        /// puis alloue le tableau de pixel dans le tas (image noire)
        Image (unsigned int dimensionX, unsigned int dimensionY);

        /// Destructeur de la classe: déallocation de la mémoire du tableau de pixels
        /// et mise à jour des champs dimx et dimy à 0
        ~Image ();

        /// Accesseur : récupère le pixel original de coordonnées (x,y) en vérifiant leur validité
        /// la formule pour passer d'un tab 2D à un tab 1D est tab[y*dimx+x]
        Pixel& getPix(const unsigned int x, const unsigned int y) const;

        /// Mutateur : modifie le pixel de coordonnées (x,y)
        void setPix(const unsigned int x, const unsigned int, const Pixel& couleur) const ;

        /// Dessine un rectangle plein de la couleur dans l'image (en utilisant setPix, indices en paramètre compris)
        void dessinerRectangle(unsigned int Xmin, unsigned int Ymin, unsigned int Xmax, unsigned int Ymax, Pixel couleur);

        /// Efface l'image en la remplissant de la couleur en paramètre
        /// (en appelant dessinerRectangle avec le bon rectangle)
        void effacer(Pixel couleur);

        // Affiche l'image dans une fenêtre SDL2
        void afficher();

        /// Effectue une série de tests vérifiant que le module fonctionne et
        /// que les données membres de l'objet sont conformes
        void testRegression();

        /// Sauvegarde l'image courante dans un fichier
        void sauver(const std::string & filename) const;

        /// Remplace une image par celle présente dans le fichier ouvert
        void ouvrir(const std::string & filename);

        /// Affiche une image
        void afficherConsole();

        void SDL_ZoomIn(SDL_Rect rect);

        void SDL_ZoomOut(SDL_Rect rect);
};