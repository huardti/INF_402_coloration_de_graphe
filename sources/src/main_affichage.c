#include <stdio.h>
#include <math.h>

#include "ecrire_graphe.h"

#include "bmp.h"
#include "graphe.h"
#include "option.h"

typedef struct point_ {
    int x;
    int y;
}point;

void calcul_pos(point centre, int n, int r, point *retour){
    Color c = {0,0,0};
    float pi = 3.14;
    point tmp;
    for (size_t i = 0; i < n; i++) {
        tmp.x = centre.x + r*cos(2*pi*i/n);
        tmp.y = centre.y + r*sin(2*pi*i/n);
        retour[i] = tmp;
    }
}

int main(int argc, const char* argv[]) {
    palette p;

    char * file_graphe = NULL;
    char * file_coloration = NULL;
    char * file_out = "./graphe.bmp";

    if (argc != 3) {
        usage_aff(argv[0]);
        return 1;
    }
    else {
        file_graphe = argv[1];
        file_coloration = argv[2];
    }

    graphe g;
    g = readFile(file_graphe, 2);
    p = init_palette();
    
    #ifdef _DEBUG
        printf("\nnombre de couleur dans la palette :%d\n\n", p.nb_color);
    #endif // _DEBUG

    Image *I;
    coloriage coloriage_graphe;
    coloriage_graphe = assigne_color(&g, p, file_coloration);

    I = NouvelleImage(1000,1000);

    int distance_centre = 400;
    point centre = {500,500};
    point tab_centre[1000];

    calcul_pos(centre, g.nb_point, distance_centre, tab_centre);


    /* on trace les segments */
    sommet a,b;
    for (size_t i = 0; i < g.nb_segment; i++) {
        a = g.segments[i].a;
        b = g.segments[i].b;

        point p_a,p_b;
        p_a = tab_centre[a.id-1];
        p_b = tab_centre[b.id-1];

        traceDroite(I, p_a.x ,p_a.y, p_b.x, p_b.y, 1, p.p[0]);
    }

    /* tracer les points en fonction de la couleur */
    for (size_t i = 0; i < g.nb_point; i++) {
        if (coloriage_graphe.point[i] + 1 > p.nb_color) {
            fprintf(stderr, "il manque des couleurs dans le fichier palette.param\n");
            exit(1);
        }
        tracerRond(I, 50, tab_centre[i].x, tab_centre[i].y, p.p[coloriage_graphe.point[i] + 1]);
    }

    Sauver(I, "test.bmp");

    return 1;
}