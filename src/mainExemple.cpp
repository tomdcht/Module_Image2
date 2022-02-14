#include "Image.h"

int main() {

    Pixel bleu(0,0,255);
    Pixel blanc(255,255,255);
    Pixel rouge(255,0,0);

    Image im1(3,2);
    im1.effacer(blanc);
    im1.sauver("./data/white.ppm");
    im1.dessinerRectangle(0,0, 2, 1, bleu);
    im1.afficherConsole();
    im1.ouvrir("./data/white.ppm");

}