#ifndef _BMP_H_
#define _BMP_H_

typedef unsigned char uint_8; /* 0  ->255 */
typedef short int16;
typedef int int32;

typedef struct Color_{
	 uint_8 r;
     uint_8 g;
     uint_8 b;
} Color;

typedef struct Image_{
	unsigned int width,height;
	Color* dat;
} Image;

/*cree une nouvelle image de largeur width et de hauteur height */
Image* NouvelleImage(int w,int h);

/* sauvegarde l'image I dans le fichier */
int Sauver(Image* I,const char* fichier);

/* met un pixel de l'image I a la position x y a la valeur de p */
void SetPixel(Image*,int x,int y,Color p);

/* retourne la couleur du pixel de l'image I a la position x y */
Color GetPixel(Image*,int x,int y);

/* supprime l'image I */
void DelImage(Image*);

/* edition */

/* trace un rond de rayon r a la position x,y de l'image I*/
void tracerRond(Image * I, int r, int x, int y, Color p);

/* trace une droite entre les points (x1, y1) et (x2, y2) d'epaisseur e et de couleur p */
void traceDroite(Image * I, int x1, int y1, int x2, int y2, int e, Color p);

#endif // !_BMP_H_