#include <stdio.h>
#include <ncurses.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#define NB_LIGNES 8 
#define NB_COLONNES 16


typedef struct {
    int tablette[NB_LIGNES][NB_COLONNES];
} Tablette;

typedef enum {
    JOUEUR_1,
    JOUEUR_2
} Joueur;

typedef struct {
    Tablette tablette;
    Joueur joueur;
} Position;

typedef struct {
    int x;
    int y;
} Coup;
/* Renvoie le joueur adversaire du Joueur joueur */
Joueur adversaire(Joueur joueur) {
    if (joueur == JOUEUR_1)
        return JOUEUR_2;
    return JOUEUR_1;
}
/* Renvoie une Tablette initialisée par des 1 */
Tablette creer_tablette() {
    Tablette tab;
    int i, j;
    for (i = 0 ; i < NB_LIGNES ; i++) {
        for (j = 0 ; j < NB_COLONNES ; j++) {
            tab.tablette[i][j] = 1;
        }
    }
    return tab;
}
/* Remplie les cases qui contiennet des 1 par des 0 */
void manger(Tablette *tab, int x, int y) {
    int i, j;
    assert(x >= 0);
    assert(x < NB_COLONNES);
    assert(y >= 0);
    assert(y < NB_LIGNES);
    assert(tab != NULL);
    for (i = y ; i < NB_LIGNES ; i++) {
        for (j = x ; j < NB_COLONNES ; j++) {
            tab->tablette[i][j] = 0;
        }
    }
}
/* Renvoie 1 si la case coup.x, coup.y contient 1 et 0 sinon */
int est_legal(Position pos, Coup coup) {
    if (pos.tablette.tablette[coup.y][coup.x] == 1)
        return 1;
    return 0;
}
/* Renvoie 1 si la case 0,0 contient 0 (la condition du fin du jeu) et 0 sinon */
int est_jeu_termine(Position pos, Joueur *joueur_gagnant) {
    if (pos.tablette.tablette[0][0] == 0) {
        *joueur_gagnant = pos.joueur;
        return 1;
    }
    return 0;
}
/* Verifie si le coup est legal, si c'est le cas elle fait appel a la fonction
*  manger pour transformer le 1 de la case coup.x, coup.y en 0 et elle donne 
*  le droit de jouer au joueur adversaire en faisant appel a la fonction
*  joueur_adversaire */
void jouer_coup(Position *pos, Coup coup) {
    if (est_legal(*pos, coup) == 1) {
        manger(&(pos->tablette), coup.x, coup.y);
        pos->joueur = adversaire(pos->joueur);
    }
}
/* affiche des cases en utilisant des pipes, elle affiche un point dans
*  le toute premiere case */
void afficher_position(Position pos) {
    int i, j;
    if (pos.joueur == JOUEUR_1)
        mvprintw((LINES - 1) / 2, (COLS - 1) / 2, "Joueur 1 joue");
    else
        mvprintw((LINES - 1) / 2, (COLS - 1) / 2, "Joueur 2 joue");
    for (i = 0 ; i < NB_LIGNES ; i++) {
        move(i, 0);
        for (j = 0 ; j < NB_COLONNES ; j++) {
            if (i == 0 && j == 0) {
                printw("|.|");
            }
            else if (pos.tablette.tablette[i][j] == 1) {
                if (j != 0) {
                    printw(" |");
                }
                else {
                    printw("| |");
                }
            }
        }
    }
}
/* Elle recupere les coordonnees de la souris, verifie si la touche est bien dans la tablette
*  si oui, elle affecte les coordonnees de la souris aux champs du Coup coup, apres elle verifie
*  si ce coup et legal, si oui on met break */
Coup lire_coup(Position pos) {
    int touche;
    Coup coup;
    MEVENT ev;
    while (1) {
        touche = getch();
        if (touche != KEY_MOUSE || getmouse(&ev) != OK) continue;
        if (ev.y  < NB_LIGNES && ev.x / 2  < NB_COLONNES && ev.x / 2 >= 0 && ev.y >= 0) {
            coup.x = ev.x / 2;
            coup.y = ev.y;
            if (est_legal(pos, coup))
                break;
        }  
    }
    return coup;
}

int main () {
    Position pos;
    Joueur joueur_gagnant;
    Coup coup;
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    mousemask(ALL_MOUSE_EVENTS
    | REPORT_MOUSE_POSITION, NULL);

    pos.tablette = creer_tablette();
    while (!est_jeu_termine(pos, &joueur_gagnant)) {
        clear();
        afficher_position(pos);
        coup = lire_coup(pos);
        jouer_coup(&pos, coup);
        refresh();
    
    }
    clear();
    if(joueur_gagnant == JOUEUR_1){
        mvprintw((LINES - 1) / 2, ((COLS - 1) / 2) - strlen("Gagnant : 1") / 2, "Gagnant : 1");
        refresh();
    }
    else
        mvprintw((LINES - 1) / 2, ((COLS - 1) / 2) - strlen("Gagnant : 2") / 2, "Gagnant : 2");
    refresh();
    sleep(2);
    endwin();
    return 0;
}
