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
        /** \param Déclaration des composantes du pixel, unsigned char en C++ */
        unsigned char r,g,b;

    public:
        /** \brief Constructeur par défaut de la classe: initialise le pixel à la couleur noire */
        Pixel();

        /** \brief Constructeur de la classe: initialise r,g,b avec les paramètres */
        Pixel(const int nr ,const int ng,const int nb);

        /** \brief Accesseur : récupère la composante rouge du pixel */
        unsigned char getRouge () const;

        /** \brief Accesseur : récupère la composante verte du pixel */
        unsigned char getVert () const;

        /** \brief Accesseur : récupère la composante bleue du pixel */
        unsigned char getBleu() const;

        /** \brief Mutateur : modifie la composante rouge du pixel */
        /** \param nr : nouvelle couleur rouge du pixel */
        void setRouge(unsigned int nr);

        /** \brief Mutateur : modifie la composante verte du pixel */
        /** \param ng : nouvelle couleur verte du pixel */
        void setVert(unsigned int ng);

        /** \brief Mutateur : modifie la composante bleue du pixel */
        /** \param nb : nouvelle couleur bleue du pixel */
        void setBleu(unsigned int nb);

};
