#include "Position.h"


#include <stdio.h>
#include <ncurses.h>

#define NB_LIGNES 8
#define NB_COLONNES 16


int est_legal(Position pos, Coup coup) {
    if (pos.tablette.tablette[coup.y][coup.x] == 1)
        return 1;
    return 0;
}

int est_jeu_termine(Position pos, Joueur *joueur_gagnant) {
    if (pos.tablette.tablette[0][0] == 0) {
        *joueur_gagnant = pos.joueur;
        return 1;
    }
    return 0;
}

void jouer_coup(Position *pos, Coup coup) {
    if (est_legal(*pos, coup) == 1) {
        manger(&(pos->tablette), coup.x, coup.y);
        pos->joueur = adversaire(pos->joueur);
    }
}

void afficher_position(Position pos) {
    int i, j;
    if (pos.joueur == JOUEUR_1)
        mvprintw((LINES - 1) / 2, (COLS - 1) / 2, "Joueur 1 joue");
    else
        mvprintw((LINES - 1) / 2, (COLS - 1) / 2, "Joueur 2 joue");
    for (i = 0 ; i < NB_LIGNES ; i++) {
        move(i, 0);
        for (j = 0 ; j < NB_COLONNES ; j++) {
            if (i == 0 && j == 0)
                printw("|.|");
            else if (pos.tablette.tablette[i][j] == 1) {
                if (j != 0)
                    printw(" |");
                else
                    printw("| |");
            }
        }
    }
}

Coup lire_coup(Position pos) {
    int touche;
    Coup coup;
    MEVENT ev;

    while (1) {
        touche = getch();
        if (touche != KEY_MOUSE || getmouse(&ev) != OK)
            continue;
        if (ev.y  < NB_LIGNES && ev.x / 2  < NB_COLONNES && ev.x / 2 >= 0 && ev.y >= 0) {
            coup.x = ev.x / 2;
            coup.y = ev.y;
            if (est_legal(pos, coup))
                break;
        }  
    }
    return coup;
}
