#include "graphe.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

graphe creeGraphe(){
    graphe g;
    g.nb_couleur = -1;
    g.nb_segment = 0;
    g.segments = NULL;
    return g;
}

void testValiditeEntete(char *ligne, unsigned int n_l, long l_ligne){
    if (l_ligne == -1) {
        fprintf(stderr, "[ERREUR] erreur a la ligne %d un saut de ligne en trop ?\n", n_l);
        exit(1);
    }
    for (size_t i = 0; (long)i < l_ligne; i++) {
        char t = ligne[i];
        if (t == ' ') {
            fprintf(stderr, " [ERREUR] erreur a la ligne %d: %s\nTrop de nombre sur la ligne attention aux espaces !\n", n_l, ligne);
            exit(1);
        }   
    }
}
void testValiditeBody(char *ligne, unsigned int n_l, long l_ligne){
    unsigned int n_space = 0;
    size_t pos_space = 0;
    if (l_ligne == -1) {
        fprintf(stderr, "[ERREUR] erreur a la ligne %d un saut de ligne en trop ?\n", n_l);
        exit(1);
    }
    for (size_t i = 0; (long)i < l_ligne; i++) {
        char t = ligne[i];
        if (t == ' ') {
            n_space++;
            pos_space = i;
        }   
    }
    if (n_space != 1) {
        fprintf(stderr, "[ERREUR] erreur a la ligne %d: %s\nTrop de nombre sur la ligne attention aux espaces !\n", n_l, ligne);
        exit(1);
    }
    if (ligne[pos_space + 1] == '\n' || ligne[pos_space + 1] == '\0') {
        fprintf(stderr, "[ERREUR] erreur a la ligne %d: %s\nil manque un point !\n", n_l, ligne);
        exit(1);
    }
}

graphe readFile(char * file_name, int mode){
    FILE *F;
    F = fopen(file_name , "r");
    graphe g = creeGraphe();

    if (F == (FILE *)NULL){
		fprintf(stderr ,"[ERREUR] lecture_fichier_graphe: ouverture du fichier impossible\n");
        exit(1);
	}

    char *ligne;
    size_t n;
    long l_ligne;
    int nb;

    /* lecture du nombre de points */
    l_ligne = getline(&ligne, &n, F);
    testValiditeEntete(ligne, 1, l_ligne);
    nb = atoi(ligne);
    g.nb_point = nb;

    /*lecture du nombre de segments */
    l_ligne = getline(&ligne, &n, F);
    testValiditeEntete(ligne, 2, l_ligne);
    nb = atoi(ligne);
    g.nb_segment = nb;

    /* lecture des segments */
    unsigned int n_ligne = 0;
    g.segments = malloc(sizeof(segment) * g.nb_segment);

    while (!feof(F)) {
        l_ligne = getline(&ligne, &n, F);
        testValiditeBody(ligne, n_ligne + 3, l_ligne);
        
        /*==========premier point========*/
        char* pch;
        pch = strtok (ligne," ");
        nb = atoi(pch);
        if (nb < 1 || nb > (int)g.nb_point) {
            fprintf(stderr ,"[ERREUR] valeur du premier point incorrect a la ligne %d, les valeurs doivent etre comprise entre [1,%d] !\n",n_ligne + 3,g.nb_point );
            exit(1);
        }
        g.segments[n_ligne].a.id = nb;

        /*========deuxieme point========*/
        pch = strtok (NULL, " ");
        nb = atoi(pch);
         if (nb < 1 || nb > (int)g.nb_point) {
            fprintf(stderr ,"[ERREUR] valeur du deuxieme point incorrect a la ligne %d, les valeurs doivent etre comprise entre [1, %d] !\n",n_ligne + 3,g.nb_point );
            exit(1);
        }
        g.segments[n_ligne].b.id = nb;

        n_ligne ++;
    }
    if ((n_ligne) > (g.nb_segment)) {
        fprintf(stderr ,"[ERREUR] il y a trop de segments\n");
        exit(1);
    }
    if ((n_ligne) < (g.nb_segment)) {
        fprintf(stderr ,"[ERREUR] il manque des segments\n");
        exit(1);
    }

    if (mode == 1) {
        /* lecture du nombre de couleur */
        printf("avec combien de couleurs voulez vous colorer le graphe ? :");
        scanf("%d", &nb);
        if (nb < 1) {
            fprintf(stderr, "%d : valeur incorrect !\n", nb);
            exit(1);
        }
        g.nb_couleur = nb;
    }

    #ifdef _DEBUG
     printGraphe(g);
    #endif // _DEBUG

    return g;

}


void printGraphe(graphe g){
    printf("nombre de points: %d\n", g.nb_point);
    printf("nombre de segments: %d\n", g.nb_segment);
    printf("nombre de couleurs: %d\n", g.nb_couleur);
    for (size_t i = 0; i < g.nb_segment; i++) {
        printf("segment %ld:\n"
                "\tpoints %d et %d.\n"
        , i+1, g.segments[i].a.id,g.segments[i].b.id);
    }
}