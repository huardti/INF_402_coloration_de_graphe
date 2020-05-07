#ifndef _ECRIRE_GRAPHE_H_
#define _ECRIRE_GRAPHE_H_

#include "bmp.h"
#include "graphe.h"

typedef struct palette_ {
    Color p[100];
    int nb_color;

}palette;

typedef struct coloriage_ {
    int point[1000]; /* chaque case represente un point la 0 represente le point 1 ... // on asigne une couleur par point.*/
}coloriage;

palette init_palette();

coloriage assigne_color();

#endif // !_ECRIRE_GRAPHE_H_