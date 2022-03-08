/**
 * \file Pixel.h
 * \brief Programme de déclaration de la classe Pixel.
 * \author DE CLERCQ.A et DECHANET.T
 * \version 1.0
 * \date 8 février 2022
 */


/**
 * \class Pixel
 * \brief Class Pixel
 *
 * Déclaration des données membres et des fonctions de la class Pixel
 */

class Pixel {
    private:
        /// les composantes du pixel, unsigned char en C++
        unsigned char r,g,b;

    public:
        // Constructeur par défaut de la classe: initialise le pixel à la couleur noire
        Pixel();

        /// Constructeur de la classe: initialise r,g,b avec les paramètres
        Pixel(const int nr ,const int ng,const int nb);

        /// Accesseur : récupère la composante rouge du pixel
        unsigned char getRouge () const;

        /// Accesseur : récupère la composante verte du pixel
        unsigned char getVert () const;

        /// Accesseur : récupère la composante bleue du pixel
        unsigned char getBleu() const;

        /// Mutateur : modifie la composante rouge du pixel
        void setRouge(unsigned int nr);

        /// Mutateur : modifie la composante verte du pixel
        void setVert(unsigned int ng);

        /// Mutateur : modifie la composante bleue du pixel
        void setBleu(unsigned int nb);

};