/**

* \file Image.h
* \brief Définition des donées membres et des fonctions membres de la classe Image
* \version 1.0
* \date 8 Février 2022

*/

#include <string>
#include "Pixel.h"

class Image {
    private:
        Pixel *tab;     //Tableau de pixels
        int dimx, dimy; //Dimensions de l'image

    public:
        // Constructeur par défaut de la classe: initialise dimx et dimy à 0
        // ce constructeur n'alloue pas de pixel
        Image ();

        // Constructeur de la classe: initialise dimx et dimy (après vérification)
        // puis alloue le tableau de pixel dans le tas (image noire)
        Image (int dimensionX, int dimensionY);

        // Destructeur de la classe: déallocation de la mémoire du tableau de pixels
        // et mise à jour des champs dimx et dimy à 0
        ~Image ();

        // Accesseur : récupère le pixel original de coordonnées (x,y) en vérifiant leur validité
        // la formule pour passer d'un tab 2D à un tab 1D est tab[y*dimx+x]
        Pixel getPix(int x, int y) const ;

        //Mutateur : modifie le pixel de coordonnées (x,y)
        void setPix(int x, int, Pixel couleur);

        // Dessine un rectangle plein de la couleur dans l'image (en utilisant setPix, indices en paramètre compris)
        void dessinerRectangle(int Xmin, int Ymin, int Xmax, int Ymax, Pixel couleur);

        // Efface l'image en la remplissant de la couleur en paramètre
        // (en appelant dessinerRectangle avec le bon rectangle)
        void effacer(Pixel couleur);

        // Effectue une série de tests vérifiant que le module fonctionne et
        // que les données membres de l'objet sont conformes
        void testRegression();

        void Image::sauver(const std::string & filename) const;

        void Image::ouvrir(const std::string & filename);

        void Image::afficherConsole();
};