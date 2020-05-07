#ifndef _GRAPHE_H_
#define _GRAPHE_H_

typedef struct sommet_ {
    unsigned int id;
    int color;
}sommet;

typedef struct segment_ {
    sommet a;
    sommet b;
}segment;

typedef struct graphe_ {
    unsigned int nb_couleur;
    unsigned int nb_point;
    unsigned int nb_segment;
    segment * segments;
}graphe;

graphe creeGraphe();

/*mode = 1 demande le nb de couleur ne demande pas sinon*/
graphe readFile(char *, int);

void printGraphe(graphe);

#endif // !_GRAPHE_H_