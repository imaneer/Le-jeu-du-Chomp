#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include "Position.h"

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
