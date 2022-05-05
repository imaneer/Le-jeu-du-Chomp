#include "Tablette.h"

#include <stdio.h>
#include <assert.h>

#define NB_LIGNES 8
#define NB_COLONNES 16


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
