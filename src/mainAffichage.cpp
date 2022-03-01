#include "Image.h"

int main (int argc, char** argv) {

   Image image (10,10);

   Pixel bleuC (194, 241, 246);
   Pixel rouge (240, 67, 0);
   Pixel bleuF (78, 129, 250);
   Pixel beige (244, 240, 172);
   Pixel gris (192, 192, 192);
   Pixel vert (8, 212, 2);

   image.effacer(bleuC);
   image.dessinerRectangle(0,9,9,9,vert);
   image.dessinerRectangle(2,4,7,8,beige);
   image.dessinerRectangle(3,3,6,3,beige);
   image.dessinerRectangle(4,2,5,2,beige);
   image.dessinerRectangle(4,7,5,8,gris);
   image.setPix(3,5,bleuF);
   image.setPix(6,5,bleuF);
   image.dessinerRectangle(4,1,5,1,rouge);
   image.setPix(3,2,rouge);
   image.setPix(2,3,rouge);
   image.setPix(1,4,rouge);
   image.setPix(6,2,rouge);
   image.setPix(7,3,rouge);
   image.setPix(8,4,rouge);

   image.afficher();

   return 0;
}