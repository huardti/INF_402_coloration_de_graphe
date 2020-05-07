#include "ecrire_graphe.h"
#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void analyse_ligne(char * ligne, long l_ligne,  int * col, int n_l){
    int n_space = 0;
    int pos_space = 0;

    if (l_ligne == -1) {
        fprintf(stderr, "erreur ligne %d: un saut de ligne en trop ?\n", n_l);
        exit(1);
    }
    for (size_t i = 0; (long)i < l_ligne; i++) {
        char t = ligne[i];
        if (t == ',') {
            n_space++;
            pos_space = i;
        }   
    }
    if (n_space != 2) {
        fprintf(stderr, "erreur ligne %d :Trop de nombre sur la ligne il faut 3 nombres\n", n_l);
        exit(1);
    }
    if (ligne[pos_space + 1] == '\n' || ligne[pos_space + 1] == '\0') {
        fprintf(stderr, "erreur ligne %d: manque un nombre!\n", n_l);
        exit(1);
    }

    /*================*/
    char * pch;
    int c = 0;
    pch = strtok(ligne,",");
    while (pch != NULL) {
        col[c] = atoi(pch);
        pch = strtok (NULL, ",");
        c++;
    }
}

/* le fichier a une couleur par ligne, la premiere ligne est la couleur apr default*/
/* cad 3 valeurs entre 0 et 255 separe par des virgules */
/* EX :
    255,255,255
    100,100,0

  ce fichier a 2 couleurs.
*/
palette init_palette(){
    FILE *f;
    f = fopen("palette.param", "r");

    if (f == (FILE *)NULL){
		fprintf(stderr ,"fichier de parametre palette.param inexistant !\n");
        exit(1);
	}

    char *ligne = NULL;
    size_t n;
    long l_ligne;
    int col[3];
    palette pal;
    pal.nb_color = 0;
    Color c;
    int n_l = 1;

    while (!feof(f)) {
        l_ligne = getline(&ligne, &n, f);
        analyse_ligne(ligne, l_ligne, col, n_l);
        c.r = col[0];
        c.g = col[1];
        c.b = col[2];

        #ifdef _DEBUG
            printf("%d,%d,%d\n", c.r,c.g,c.b);
        #endif // _DEBUG

        pal.p[pal.nb_color] = c;
        pal.nb_color ++;
        n_l++;

    }
    return pal;
}

coloriage assigne_color(graphe *g, palette p, char * fichier_sortie_sat){
        FILE *f;
    f = fopen(fichier_sortie_sat, "r");

    if (f == (FILE *)NULL){
		fprintf(stderr ,"impossible d'ouvivr le fichier %s\n", fichier_sortie_sat);
        exit(1);
	}

    /*======test_header======*/
     char *ligne = NULL;
    size_t n;
    long l_ligne;

    l_ligne = getline(&ligne, &n, f);

    if (l_ligne == -1) {
        fprintf(stderr, "erreur dans le fichier %s\n", fichier_sortie_sat);
        exit(1);
    }
    else if (l_ligne == 6 && ligne[0] == 'U' && ligne[1] == 'N' && ligne[2] == 'S') {
        fprintf(stderr, "le graphe ne peut pas etre colorié avec ce nombre de couleur\n");
        exit(1);
    }
    else if (l_ligne == 4 && ligne[0] == 'S' && ligne[1] == 'A' && ligne[2] == 'T') {
        l_ligne = getline(&ligne, &n, f);
       
        int nb_var = 0;
        int point = 0;
        coloriage color_graph;

        /*================*/
        char * pch;
        pch = strtok(ligne," ");
        while (pch[0] != '0') {
            if (pch[0] != '-') {
                //printf("%s\n", pch);
                color_graph.point[point] = atoi(pch);
                point++;
            }
            pch = strtok(NULL," ");
            nb_var++;
        }
        int nb_color = (nb_var/point);

            printf("nombre de point : %d \nnombre de var : %d\n", point, nb_var);
        for (size_t i = 0; i < point; i++) {
            printf("point %d prend la couleur %d\n", i +1 , color_graph.point[i] % nb_color);
        }
        

        for (size_t i = 0; i < point; i++) {
            color_graph.point[i] = (color_graph.point[i] % nb_color);
        }
        return color_graph;
    }
}