#ifndef __POSITION__
#define __POSITION__

#include "Tablette.h"
#include "Joueur.h"

typedef struct{
    int x;
    int y;
}Coup;

typedef struct Position{
    Tablette tablette;
    Joueur joueur;
} Position;

int est_legal(Position pos, Coup coup);
int est_jeu_termine(Position pos, Joueur *joueur_gagnant);
void jouer_coup(Position *pos, Coup coup);
void afficher_position(Position pos);
Coup lire_coup(Position pos);

#endif
