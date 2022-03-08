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

/** \brief Constante de la largeur de la fenêtre SDL */
#define WIDTH_WINDOW 200

/** \brief Constante de la hauteur de la fenêtre SDL */
#define HEIGHT_WINDOW 200

/**
 * \class Image
 * \brief Class Image
 *
 * Déclaration des données membres et des fonctions de la class Image
 */

class Image {
    private:

        /** \param Tableau de Pixels */
        Pixel *tab;

        /** \param Dimensions de l'image */
        unsigned int dimx, dimy;

        /** \brief Fonctions gérant l'affichage avec SDL */
        void SDLAffInit();
        void SDLAffLoop();
        void SDLAffQuit();

    public:

        /** \param Paramètres permettant la création d'une fenêtre SDL*/
        SDL_Window * window;

        /** \param Paramètres permettant la création d'un rendu SDL*/
        SDL_Renderer * renderer;

        /** \param Paramètres permettant la création d'une surface SDL*/
        SDL_Surface *picture;

        /** \param Paramètres permettant la création d'une texture SDL*/
        SDL_Texture *texture;

        /** \param Rectangle de destination de notre surface*/
        SDL_Rect dest_rect = {WIDTH_WINDOW/2,HEIGHT_WINDOW/2,HEIGHT_WINDOW,HEIGHT_WINDOW};

        /** \param Rectangle source de notre surface*/
        SDL_Rect src_rect = {0,0,10,10};

        /** \brief Constructeur par défaut de la classe: initialise dimx et dimy à 0
        ce constructeur n'alloue pas de pixel*/
        Image ();

        /** \brief Constructeur de la classe: initialise dimx et dimy (après vérification)
        puis alloue le tableau de pixel dans le tas (image noire)*/
        Image (unsigned int dimensionX, unsigned int dimensionY);

        /** \brief Destructeur de la classe: déallocation de la mémoire du tableau de pixels
        et mise à jour des champs dimx et dimy à 0 */
        ~Image ();

        /** \brief Accesseur : récupère le pixel original de coordonnées (x,y) en vérifiant leur validité
        la formule pour passer d'un tab 2D à un tab 1D est tab[y*dimx+x] */
        Pixel& getPix(const unsigned int x, const unsigned int y) const;

        /** \brief Mutateur : modifie le pixel de coordonnées (x,y) */
        void setPix(const unsigned int x, const unsigned int, const Pixel& couleur) const ;

        /** \brief Dessine un rectangle plein de la couleur dans l'image (en utilisant setPix, indices en paramètre compris) */
        void dessinerRectangle(unsigned int Xmin, unsigned int Ymin, unsigned int Xmax, unsigned int Ymax, Pixel couleur);

        /** \brief Efface l'image en la remplissant de la couleur en paramètre
        (en appelant dessinerRectangle avec le bon rectangle) */
        void effacer(Pixel couleur);

        /** \brief Affiche l'image dans une fenêtre SDL2 */
        void afficher();

        /** \brief Effectue une série de tests vérifiant que le module fonctionne et
        que les données membres de l'objet sont conformes */
        void testRegression();

        /** \brief Sauvegarde l'image courante dans un fichier */
        /** \param filename : nom du fichier */
        void sauver(const std::string & filename) const;

        /** \brief Remplace une image par celle présente dans le fichier ouvert */
        /** \param filename : nom du fichier */
        void ouvrir(const std::string & filename);

        /** \brief Affiche les données d'une image dans la console */
        void afficherConsole();

        /** \brief Zoom sur l'image affiché dans la fenêtre SDL */
        void SDL_ZoomIn(SDL_Rect rect);

        /** \brief Dézoom sur l'image affiché dans la fenêtre SDL */
        void SDL_ZoomOut(SDL_Rect rect);
};